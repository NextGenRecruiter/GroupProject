#include <iostream>
#include <cstdio>
#include <fstream>
#include "SequenceSet.h"
#include <string>
#include <sstream> 


/*
  Here we have the first constructor for the SequenceSet
  @param int f_count, int b_size, int r_size
  @return SequenceSet
  @purpose  this will initialize some of our data and open the file

*/
SequenceSet::SequenceSet(int f_count, int b_size, int r_size){
  field_count = f_count;
  block_size = b_size;
  record_size = r_size;
  in_filename = "us_postal_codes_formatted.txt";
  first = NULL;
  
  load();
}

/*
  Here we have the second constructor for the SequenceSet
  @param int f_count, int b_size, int r_size
  @return SequenceSet
  @purpose  this will initialize some of our data and open the file

*/
SequenceSet::SequenceSet(int f_count, int b_size, int r_size, int d_cap, std::string i_filename, std::string o_filename){
  field_count = f_count;
  block_size = b_size;
  record_size = r_size;
  default_cap = d_cap;
  in_filename = i_filename;
  out_filename = o_filename;
  first = NULL;
  
  load();
}

/*
  Here we have the first constructor for the SequenceSet
  @param int f_count, int b_size, int r_size
  @return SequenceSet
  @purpose  this will initialize some of our data and open the file

*/
SequenceSet::~SequenceSet(){
  delete(&field_count, &block_size, &record_size, &default_cap, &in_filename, &out_filename);
}


/*
  Method: Create
  param:
  return:
  purpose:
  here we take the data file and create the sequence set file

*/
void SequenceSet::create(){

}

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

  std::string field_name_identifier = "Field Name  ";
  std::string column_range_identifier = "   column range    ";
  std::string type_identifier = "   type ";

  int index_of_field_name = -1;
  int index_of_collum_size = -1;
  int index_of_type = -1;

  //skip a line for it gives details on what each section means, and thats just a switch with some hard code like 'Field Name'
  std::getline(in_file, line);
  std::vector<std::string> field_data_positions = split_string(line, '|');
  for (int i = 0; i < field_data_positions.size(); i++){
    if (!field_data_positions[i].compare(field_name_identifier)){
      index_of_field_name = i;
    }
    if (!field_data_positions[i].compare(column_range_identifier)){
      index_of_collum_size = i;
    }
    if (!field_data_positions[i].compare(type_identifier)){
      index_of_type = i;
    }
  }


  //start a counter
  int i = 0;
  //go while we still have lines and are not taking too many fields
  while (std::getline(in_file, line) && i < field_count){
    //if we find the end of header tag then break
    if(!end_of_header.compare(line))
      break;
    
    std::vector<std::string> field_data_split = split_string(line, '|');
    field_labels.push_back(field_data_split[index_of_field_name]);
    field_sizes.push_back(field_data_split[index_of_collum_size]);
    field_types.push_back(field_data_split[index_of_type]);

    i++;
  }

  in_file.close();
}


/*
  Method: is_open
  param:
  return:
  purpose:

*/
bool SequenceSet::is_open(){

  return false;
}


/*
  Method: search
  param:
  return:
  purpose:

*/
int SequenceSet::search(){

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

}


/*
  Method: developer_show
  param:
  return:
  purpose:

*/
void SequenceSet::developer_show(){
  std::cout << "field_count:\t" << field_count << "\n";

  std::cout << "field_labels:\t";
  for(std::string s: field_labels){
    std::cout << s << "\t";
  }
  std::cout << "\n";

  std::cout << "field_sizes:\t";
  for(std::string s: field_sizes){
    std::cout << s << "\t";
  }
  std::cout << "\n";

  std::cout << "field_types:\t";
  for(std::string s: field_types){
    std::cout << s << "\t";
  }
  std::cout << "\n";
}