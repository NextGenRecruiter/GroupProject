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

  std:string word;

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


/*   Class Methods   */

/*
  Here we have the first constructor for the SequenceSet i think this will be deleted in the end
  @param  int b_size, int r_size
  @return n/a
  @purpose  this will initialize some of our data and open the file to default

*/
SequenceSet::SequenceSet(int b_size, int r_size){
  block_size = b_size;
  record_size = r_size;
  in_filename = "us_postal_codes_formatted.txt";
  out_filename = "us_postal_codes_sequence_set_file.txt";
  first = NULL;
  
  load();
}

/*
  Here we have the constructor for the SequenceSet that takes in all the values relivant to the header and saving
  @param int b_size, int r_size, int d_cap, std::string i_filename, std::string o_filename
  @return n/a
  @purpose  this will initialize some of our data and open the file and output file

*/
SequenceSet::SequenceSet(int b_size, int r_size, int d_cap, std::string i_filename, std::string o_filename){
  block_size = b_size;
  record_size = r_size;
  default_cap = d_cap;
  in_filename = i_filename;
  out_filename = o_filename;
  first = NULL;
  
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

  std::string end_of_header = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  //here i am making the header components to be at the top of the file 
  std::string file_type = "ascii";
  std::string header_record_size = "22 lines";
  block_size = 512;
  default_cap = 50;
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
  std::string end_of_header = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  in_file.open(in_filename);

  //if the file ended then tell the user and exit
  if (in_file.fail()) {
    cerr << "Error opening file: " << in_filename;
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
      stringstream field_count_string(spaceless_line[1]);
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
int SequenceSet::search(int primKey){
  int offset;
  string line;

  ifstream in_file;
  in_file.open("us_postal_codes_formatted.txt");

  std::cout<<"Enter the primary key of the record you want to search: "<<std::endl;
  std::cin>>primKey;

  if(in_file.is_open())
  {
    while(!in_file.eof()){
      getline(in_file, line);
      if(offset = line.find(primKey, 0) != string::npos){
        std::cout<<"The record has been found " << primKey << std::endl;
      }
    }
    in_file.close();
  }else
  {
    std::cout<<"Record not found"<<std::endl;
  }
  
  return 0;
}


/*
  Method: populate
  param:
  return:
  purpose:

*/
void SequenceSet::populate(){

  

}


/*
  Method: insert
  param:
  return:
  purpose:

*/
void SequenceSet::insert(){

}


/*
  Method: remove
  param:
  return:
  purpose:

*/
void SequenceSet::del(){
 
}


/*
  Method: update
  param:
  return:
  purpose:

*/
void SequenceSet::update(){

}


/*
  Method: display_record
  param:
  return:
  purpose:

*/
void SequenceSet::display_record(){

}

/*
  Method: display_field
  param:
  return:
  purpose:

*/
void SequenceSet::display_field(){

}


/*
  Method: display_file
  param:
  return:
  purpose:

*/
void SequenceSet::display_file(){

}


/*
  Method: display_SS
  param:
  return:
  purpose:

*/
void SequenceSet::display_SS(){

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
  
    ifstream in_file; 
    in_file.open("us_postal_codes_formatted.txt", ios::in | ios::binary); 
  
    ofstream out_file; 
    out_file.open("us_postal_codes_sequence_set_file.txt", ios::out | ios::binary); 
  
    while (!in_file.eof()) { 
  
        in_file.read((char*)this, sizeof(SequenceSet)); 
  
        // if(in_file)checks the buffer record in the file 
        if (in_file) { 

            int primarykey = 0;
  
            // comparing the primKey with 
            // primary key of record to be deleted 
            if (primKey == primarykey) { 
                flag = 1; 
                cout << "The deleted record is \n"; 
  
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
        cout << "\nrecord successfully deleted \n"; 
    else
        cout << "\nrecord not found \n"; 

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