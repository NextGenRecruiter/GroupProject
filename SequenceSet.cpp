#include <iostream>
#include <cstdio>
#include <fstream>
#include "SequenceSet.h"
#include <string>
#include <sstream>

/*   Utility Methods  */

//This function will take apart a string and split it by some char delimeter
std::vector<std::string> split_string(std::string str, char delimiter){
  std::vector<std::string> split_str;
  std::string word;

  for(char x : str){

    if (x == delimiter){
      split_str.push_back(word);
      word = ""; 
    }else{ 
      word = word + x; 
    }

  }
  split_str.push_back(word);
  return split_str;
}

std::vector<char> string_to_vector(std::string s, int n){
  std::vector<char> v;
  v.push_back(n);
  for (char c : s){
    v.push_back(c);
  }
  return v;
}

std::string add_c_to_a_til_size_of_b(std::string a,std::string b,std::string c, bool front = true){
  int size_to_be = b.size();
  std::string new_a = a;
  while(new_a.size() < size_to_be){
    if(front){
      new_a = c + new_a;
    }else{
      new_a = new_a + c;
    }
  }
  return new_a;
}


/*   Class Methods   */

/*
  Here we have the first constructor for the SequenceSet i think this will be deleted in the end
  @param  int b_size, int r_size
  @return n/a
  @purpose  this will initialize some of our data and open the file to default

*/
SequenceSet::SequenceSet(){
  block_size = 8;  //records per block
  record_size = 1; //characters per record
  in_filename = "us_postal_codes_formatted.txt";
  out_filename = "us_postal_codes_sequence_set_file.txt";
  default_cap = 0.5;
  primary_key_index = 0;
  first = NULL;
  end_of_header = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  
  load();
}

/*
  Here we have the constructor for the SequenceSet that takes in all the values relivant to the header and saving
  @param int b_size, int r_size, int d_cap, std::string i_filename, std::string o_filename
  @return n/a
  @purpose  this will initialize some of our data and open the file and output file 
  this is the constructor for the header

*/
SequenceSet::SequenceSet(int b_size, int r_size, float d_cap, std::string i_filename, std::string o_filename){
  block_size = b_size;
  record_size = r_size;
  default_cap = d_cap;
  in_filename = i_filename;
  out_filename = o_filename;
  primary_key_index = 0;
  first = NULL;
  end_of_header = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  
  load();
}

/*
  Here we have the first destructor for the SequenceSet
  @param n/a
  @return n/a
  @purpose  this free memory

*/
SequenceSet::~SequenceSet(){
  delete(&field_count, &block_size, &record_size, &default_cap, &in_filename, &out_filename);
}


/*
  Method: create
  param:none
  return:none
  purpose: this will create the empty file with just the header and any data in the data array

  Your header record should include the following components:
    --sequence set file type
    --header record size
    --block size {default to (512B / block)}
    --maximum count of records per block
        --minimum capacity: 50%
        -(for simplicity, require an even number) 
    --record size
    --count of fields per record
    --field info triple (tuple) {AoS or SoA}
        --name or ID
        --size
        --type schema
            -(format to read or write) 
    -indicate field which serves as the primary key
    --pointer to the block avail-list
    -pointer to the active sequence set list
    -block count
    -record count
    -stale flag
    -Simple Index (10.3)
        -file name
        -schema information 

*/
void SequenceSet::create(){
  //here i am making the header components to be at the top of the file 
  std::string file_type = "ascii";
  std::string header_record_size = "22 lines";
  block_size = 512;
  record_size = -1;
  int max_record_count = -1;
  int f_count = field_count;
  Block* block_avail = first;
  Index* active_list = root;
  int block_count = 0;
  int record_count = 0;
  bool stale = false;

  //here is a disign desicion: SoA or AoS here structure
  struct field_tuple{
    std::string label;
    std::string size;
    std::string type;

    field_tuple(std::string a,std::string b,std::string c){
      label = a;
      size = b;
      type = c;
    };
  };
  //here is an array of structures
  std::vector<field_tuple> fields;
  for (int i = 0; i < field_count; i++){
    fields.push_back(field_tuple(field_labels[i],field_sizes[i],field_types[i]));
  }
  
  out_file.open(out_filename);

  //write the header
  out_file << "File Type: " << file_type << "\n";
  out_file << "Header Size: " <<  header_record_size << "\n";
  out_file << "Block Size: " <<  block_size << "\n";
  out_file << "Maximum Records: " << max_record_count  << "\n";
  out_file << "Minimum Capacity: " << default_cap  << "%\n";
  out_file << "Record Size: " <<  record_size << "\n";
  out_file << "Record Field Count: " << field_count  << "\n";
  for (field_tuple f : fields){
    out_file << f.label << '|' << f.size << '|' << f.type << "\n";
  }
  out_file << "Primary Key: " << field_labels[0] << "\n";
  out_file << "Avail Block Pointer: " <<  block_avail  << "\n";
  out_file << "Active List: " <<  active_list << "\n";
  out_file << "Block Count: " <<  block_count  << "\n";
  out_file << "Record Count: " <<  record_count << "\n";
  out_file << "Stale Flag: " <<  stale << "\n";
  out_file << out_filename << "\n";
  out_file << "This file is for loading blocks into a sequence set." << "\n";
  out_file << end_of_header << "\n";

  close();
}


/*
  Method: load
  param:
  return:
  purpose:
  here we load blocks from the sequence set file into ram
*/
void SequenceSet::load(){
  //create a local file for loading in that data
  std::string line = "";
  in_file.open(in_filename);

  //if the file ended then tell the user and exit
  if (in_file.fail()) {
    exit(1);
  }

  //go through each line of the file
  while(std::getline(in_file, line)){
    //if we find the end of header tag then break
    if(!end_of_header.compare(line))
      break;
    
    //cut it into words. look for "Fields:"
    //Record the feilds and stop
    std::vector<std::string> spaceless_line = split_string(line, ' ');
    if (!spaceless_line[0].compare("Fields:")){
      std::stringstream field_count_string(spaceless_line[1]);
      field_count_string >> field_count;
      break;
    }
  }

  //here are the strings to find what field is in what spot. a function to strip spaces would be ideal here
  std::string field_name_identifier = "Field Name  ";
  std::string column_range_identifier = "   column range    ";
  std::string type_identifier = "   type ";

  //here are the store of index's for what in what order
  int index_of_field_name = -1;
  int index_of_collum_size = -1;
  int index_of_type = -1;

  //get the line
  std::getline(in_file, line);
  //split it into section
  std::vector<std::string> field_data_positions = split_string(line, '|');
  //for each one see if it is one of the identifiers above and if so store its location
  for (int i = 0; i < field_data_positions.size(); i++){
    if (!field_data_positions[i].compare(field_name_identifier))
      index_of_field_name = i;
    if (!field_data_positions[i].compare(column_range_identifier))
      index_of_collum_size = i;
    if (!field_data_positions[i].compare(type_identifier))
      index_of_type = i;
  }


  //start a counter
  int i = 0;
  //go while we still have lines and are not taking too many fields
  while (std::getline(in_file, line) && i < field_count){
    //if we find the end of header tag then break
    if(!end_of_header.compare(line))
      break;
    
    //take each line which will house the field data
    std::vector<std::string> field_data_split = split_string(line, '|');
    //chop it and put it into the correct vector to be used later.
    field_labels.push_back(field_data_split[index_of_field_name]);
    field_sizes.push_back(field_data_split[index_of_collum_size]);
    field_types.push_back(field_data_split[index_of_type]);

    //increase since we have another field that was specified
    i++;
  }

  //close files
  close();
}


/*
  Method: close
  param:none
  return:none
  purpose:close files if needed

*/
void SequenceSet::close(){
  if (in_file.is_open()) {
    in_file.close();
  }
  if (out_file.is_open()) {
    out_file.close();
  }
}


/*
  Method: is_open
  param: int flag 
      0 - file
      1 - block
      2 - record
      3 - field
  return: bool true if empty and false if populated
  purpose: to know the state of a structure

  if nothing is given but the flag then it will do input/output on command line for user
  and will take in the index's of requested whatever structure and tell you its status

*/
bool SequenceSet::is_empty(int flag, int block = -1, int record = -1, int field = -1){
  //this will check the status of requested
  bool status;

  if(flag == 0){ // file or the whole linked list
    status = (first == NULL);
  }

  if(flag == 1){ // block

    if (block == -1){
      std::cout << "Index of Block to check: ";
      std::cin >> block;
    }

    Block *b = first;
    while(block > 0){
      status = (b==NULL);
      b = b -> next;
      block--;
    }

  }

  if(flag == 2){ // record
    if (block == -1){
      std::cout << "Index of Block to check: ";
      std::cin >> block;
    }

    Block *b = first;
    while(block > 0){
      status = (b==NULL);
      b = b -> next;
      block--;
    }

    if(!status){//block is valid
      if (record == -1){
        std::cout << "Index of Record to check: ";
        std::cin >> record;
      }

      status = (b -> data[record][0] == ' ');

    }
  }

  if(flag == 3){ // field
    if (block == -1){
      std::cout << "Index of Block to check: ";
      std::cin >> block;
    }

    Block *b = first;
    while(block > 0){
      status = (b==NULL);
      b = b -> next;
      block--;
    }

    if(!status){//block is valid
      if (record == -1){
        std::cout << "Index of Record to check: ";
        std::cin >> record;
      }

      status = (b -> data[record][0] == ' ');

      if (!status){
        if (field == -1){
          std::cout << "Index of Field to check: ";
          std::cin >> field;
        }

        status = (b -> data[record][field] == ' ');
      }
    }
  }

  return status;
}


/*
  Method: search
  param:
  return:
  purpose:

*/
int SequenceSet::search(std::string search_term){
  
  
  return 0;
}


/*
  Method: populate
  param:
  return:
  purpose:
  we count blocks and records.
  we open the file and skip the header and loop the rest
  we create an empty node for a btree

*/
void SequenceSet::populate(){
  int record_number;          //current record being coppied
  int block_count = -1;      //current block number  int primary_key_i;

  int primary_key_int;
  std::string primary_key_tmp;
  int index_place = -1, node_count = 0;


  Block *prev;
  Index *current_node = new Index; //pointer to current node  in_file.open(in_filename);
  
  std::string line = "";

  in_file.open(in_filename);

  while(std::getline(in_file,line)){
    if(!line.compare(end_of_header)){
      break;
    }
  }

  while(!in_file.eof()){
    record_number = 0;

    //make btree node as neccessary
    if(++index_place%3 == 0){ // make a new node every 3 primary keys
      if(node_count++ > 0){ //first node skips this
        current_node->nextNode = new Index; //move onto next node
        current_node = current_node->nextNode; // remember where we are
      }else //node count is 0
        root = current_node; //if first then its the root
      
      for (int i = 0; i < 4; i++){ //fill the children of the b tree
        current_node -> key[i] = -1;
        current_node -> block[i] = NULL;
        current_node -> block[i] = NULL;
      }
      current_node -> nextNode = NULL;
      current_node -> parent = NULL;
    }

    //make next (or first) Block:
    Block *b = new Block;               //get the empty block
    b -> previous = NULL;               //prev is null
    b -> next = NULL;                   //next too
    b -> data.resize(block_size);       //resize the array to be the length of the block sizes
    for(int i = 0; i < block_size; i++){
      b -> data[i] = "";    //resize it for the length of a record   //ERROR
    }
    if(++block_count != 0){             //increase block count each iteration, and if it isnt 0 like the first iteration then set the first in the sequence set to be b
      b -> previous = prev;             //if not then send it to the next node.
      prev -> next = b;
    }
    else
      first = b;
    prev = b;


    //while block isn't __% full, keep filling:
    std::string line;
    while(record_number < (block_size * default_cap) && !in_file.eof()){
      std::getline(in_file, line);
      if(line != " "){
        //std::cout << record_number << "  -" << line << "-\n";
        prev -> data[record_number] = add_c_to_a_til_size_of_b(std::to_string(record_number), std::to_string(block_size), "0") + line;
        record_number++;
      }
    }

    //get the primary key and add it to the tree DO CONTINUE ON FROM HERE
    std::string tmp = prev->data[record_number];
    primary_key_tmp = tmp.substr(0,5);
    primary_key_tmp.resize(6);
    primary_key_int = atoi(primary_key_tmp.c_str());
    current_node -> key[index_place%3] = primary_key_int;
    current_node -> block[index_place%3] = prev;

    prev -> records_count = record_number;

  }
  delete(prev);
  
  //Build the B+ tree up from the "linked list" structure


  close();
}


/*
  Method: insert
  param:
  return:
  purpose:

*/
void SequenceSet::insert(std::string new_record){
  Block *b = first;
  bool placed = false;

  while( b != NULL && !placed){
    if(b -> records_count < block_size){
      b -> records_count++;
      b -> data[b -> records_count] = new_record;
      placed = true;
    }
    b = b -> next;
  }

  //all blocks filled make a new one
  if(!placed){
    Block *new_b = new Block;
    new_b -> previous = b;
    b -> next = new_b;
    new_b -> records_count++;
    new_b -> data[b -> records_count - 1] = new_record;
  }
}


/*
  Method: remove
  param:
  return:
  purpose:

*/
void SequenceSet::delete_record(int block = -1, int record = -1){
  Block *b = first;
  int b_count = 0, r_count;

  if(block == -1){
    std::cout << "Enter block index: " << std::endl;
    std::cin >> block;
  }
  if(record == -1){
    std::cout << "Enter record index: " << std::endl;
    std::cin >> record;
  }

  while( b != NULL && b_count < block){
    b_count++;
    b = b -> next;
  }

  if (record > 0 && record < b -> records_count){
    b -> data[record] = "";
  }

  delete(b);
}


/*
  Method: update
  param:
  return:
  purpose:

*/
void SequenceSet::update(int record, int field, std::string new_field){
  Block *b = first;
  int r_count = 0;

  if(record == -1){
    std::cout << "Enter record index: " << std::endl;
    std::cin >> record;
  }

  while( b != NULL && r_count < record){
    r_count = r_count + b -> records_count;
    b = b -> next;

    if(r_count > record){

        if (record > 0 && record < b -> records_count){    
        std::string before, after, new_record;

        std::vector<int> range = get_field_range_tuple(field);

        before = b -> data[record].substr(0,range[0]);
        after = b -> data[record].substr(range[1], b -> data[record].size());

        new_record = before + new_field + after;
        b -> data[record] = new_record;
      }
    }
  }
  delete(b);
}


/*
  Method: display_record
  param:
  return:
  purpose:

*/
void SequenceSet::display_record(int record = -1, int block = -1){
  Block *b = first;
  int b_count = 0;

  while(block < 0){
    std::cout << "\nEnter block index: ";
    std::cin >> block;
  }
  while(record < 0){
    std::cout << "\nEnter record index: ";
    std::cin >> record;
  }

  while( b != NULL && b_count < block){
    b_count++;
    b = b -> next;
  }

  std::string record_s = "*Record Not Found*";
  if(b != NULL){
    int size = b->records_count;
    if(record >= 0 && record < size){
      record_s = b -> data[record];
    }else if(record >= 0 && record <= block_size){
      record_s = "*Empty Record*";
    }
  }

  std::cout << "\n\'" << record_s << "\'\n";
  delete(b);
}

/*
  Method: display_field
  param:
  return:
  purpose:

*/
void SequenceSet::display_field(int field = -1, int record = -1, int block = -1){
  Block *b = first;
  int b_count = 0;

  while(block < 0){
    std::cout << "\nEnter block index: ";
    std::cin >> block;
  }
  while(record < 0){
    std::cout << "\nEnter record index: ";
    std::cin >> record;
  }
  while(field < 0){
    std::cout << "\nEnter field index: ";
    std::cin >> field;
  }

  while( b != NULL && b_count < block){
    b_count++;
    b = b -> next;
  }

  std::string record_s = "*Record Not Found*";
  if(b != NULL){
    int size = b->records_count;
    if(record >= 0 && record < size){
      record_s = b -> data[record];

      if(field >= 0 && field < field_count){
        std::vector<int> ranges = get_field_range_tuple(field);
        std::string field_s = record_s.substr(ranges[0]-1 + std::to_string(block_size).size(), (ranges[1] - (ranges[0]-2)));
        std::cout << "\n\'" << ranges[0] << "-" << ranges[1] << "\'\n";
        std::cout << "\n\'" << field_s << "\'\n";
        return;
      }

    }else if(record >= 0 && record <= block_size){
      record_s = "*Empty Record*";
      std::cout << "\n\'" << record_s << "\'\n";
    }
  }

  std::cout << "\n\'" << record_s << "\'\n";
  delete(b);
}


/*
  Method: display_file
  param:
  return:
  purpose:

*/
void SequenceSet::display_file(int limit = -1){
  if(limit == -1){limit = block_size;}
  Block *b = first;
  int count = 0;
  while( b != NULL && count < limit){
    std::cout << "Block " << count << "\n";
    std::cout << "Records in Block " << count << ": " << b -> records_count << "\n";
    std::cout << "Head of Records: \n" << b -> data[0] << "\n";
    int last = b -> records_count - 1;
    std::cout << "Tail of Records: \n" << b -> data[last] << "\n\n";
    count++;
    b = b -> next;
  }
  delete(b);
}


/*
  Method: display_SS
  param:
  return:
  purpose:

*/
void SequenceSet::display_SS(){
  Block *b = first;
  int count = 0;
  std::string empty_records_index_string;
  while( b != NULL){
    std::cout << "\nBlock " << count << "\n";
    std::cout << "Records in Block " << count << ": " << b -> records_count << "\n";
    int r_count = 0;
    empty_records_index_string = "[";
    for(std::string r : b -> data){
      if(r != ""){
        std::cout << "Record " << r_count << ": \"" << r << "\"\n";
        r_count++;
      }else{
        empty_records_index_string = empty_records_index_string + std::to_string(r_count) + ", ";
        r_count++;
      }
    }
    std::cout << "Empty Records: " << empty_records_index_string << "]\n";
    std::cout << "\n\n";

    std::cout << "Press enter to see next block...(Ctrl + C to stop)";
    getchar();

    count++;
    b = b -> next;
  }
  delete(b);
}


/*
  Method: validate
  param:
  return:
  purpose:

*/
void SequenceSet::validate(){

}


/*
  Method: addIndex
  param:
  return:
  purpose:

*/
void SequenceSet::addIndex(int primKey, Block *b){

}


/*
  Method: delIndex
  param:
  return:
  purpose:

*/
void SequenceSet::delIndex(int primKey){
   int flag = 0; 
  
    std::ifstream in_file; 
    in_file.open("us_postal_codes_formatted.txt", std::ios::in | std::ios::binary); 
  
    std::ofstream out_file; 
    out_file.open("us_postal_codes_sequence_set_file.txt", std::ios::out | std::ios::binary); 
  
    while (!in_file.eof()) { 
  
        in_file.read((char*)this, sizeof(SequenceSet)); 
  
        // if(in_file)checks the buffer record in the file 
        if (in_file) { 

            int primarykey = 0;
  
            // comparing the primKey with 
            // primary key of record to be deleted 
            if (primKey == primarykey) { 
                flag = 1; 
                std::cout << "The deleted record is \n"; 
  
                // display the record 
                display_SS(); 
            } 
            else { 
                // copy the record of "us_postal_codes_formatted.txt" file to "us_postal_codes_sequence_set_file.txt" file 
                out_file.write((char*)this, sizeof(SequenceSet)); 
            } 
        } 
    } 
  
    out_file.close(); 
    in_file.close(); 
  
    // delete the old file 
    remove("us_postal_codes_formatted.txt"); 
  
    // rename new file to the older file 
    rename("us_postal_codes_sequence_set_file.txt", "us_postal_codes_formatted.txt"); 
  
    if (flag == 1) 
        std::cout << "\nrecord successfully deleted \n"; 
    else
        std::cout << "\nrecord not found \n"; 

}


/*
  Method: developer_show
  param:
  return:
  purpose:

*/
void SequenceSet::developer_show(){
  std::cout << "field_count:\t" << field_count << "\n";

  std::cout << "field_labels|field_sizes|field_types \n";
  for (int i = 0; i < field_labels.size(); i++){
    std::cout << field_labels[i] << "|" << field_sizes[i] << "|" << field_types[i] << "\n";
  }
  std::cout << "\n";
}

/*
often we want where the characters index is in the recod
which is stored in the range
but extracting that range isnt easy so heres a function to do it

*/

std::vector<int> SequenceSet::get_field_range_tuple(int field_index){
  std::string s = field_sizes[field_index];
  std::vector<std::string> sub_s = split_string(s, '-');
  int low = atoi(sub_s[0].c_str());
  int high = atoi(sub_s[1].c_str());
  std::vector<int> r = {low,high};
  return r;
}