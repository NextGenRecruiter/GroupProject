#include<iostream>
#include <cstdio>
#include <fstream>
#include "SequenceSet.h"


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


/*
  Method: load
  param:
  return:
  purpose:
  here we load blocks from the sequence set file into ram
*/
void SequenceSet::load(){
  fstream in_file;
  std::string line = "";
  std::string end_of_header = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  in_file.open(in_filename);

  if (in_file.fail()) {
    cerr << "Error opening file: " << in_filename;
    exit(1);
  }

  while(std::getline(in_file, line)){
    if(!end_of_header.compare(line))
      break;
    
    //https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
    //cut it into words. look for fields
    //record the feilds and pull each line after and chop it into vectors field_labels and field_sizes
    std::cout << line << std::endl;
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