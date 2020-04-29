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
  first = NULL;
  
  load();
}

/*
  Here we have the second constructor for the SequenceSet
  @param int f_count, int b_size, int r_size
  @return SequenceSet
  @purpose  this will initialize some of our data and open the file

*/
SequenceSet::SequenceSet(int f_count, int b_size, int r_size, int d_cap, fstream i_file, fstream o_file){
  field_count = f_count;
  block_size = b_size;
  record_size = r_size;
  default_cap = d_cap;
  in_file = i_file;
  out_file = o_file;
  first = NULL;
  
  load();
}


/*
  Method: Create
  param:
  return:
  purpose:
  here we take the data file and create the sequence set file

*/
void SequenceSet::create(){

  return 0;
}


/*
  Method: load
  param:
  return:
  purpose:
  here we load blocks from the sequence set file into ram
*/
void SequenceSet::load(){

  return 0;
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

  return 0;
}


/*
  Method: insert
  param:
  return:
  purpose:

*/
void SequenceSet::insert(){

  return 0;
}


/*
  Method: remove
  param:
  return:
  purpose:

*/
void SequenceSet::del(){

  return 0;
}


/*
  Method: update
  param:
  return:
  purpose:

*/
void SequenceSet::update(){

  return 0;
}


/*
  Method: display_record
  param:
  return:
  purpose:

*/
void SequenceSet::display_record(){}

/*
  Method: display_field
  param:
  return:
  purpose:

*/
void SequenceSet::display_field(){}


/*
  Method: display_file
  param:
  return:
  purpose:

*/
void SequenceSet::display_file(){}


/*
  Method: display_SS
  param:
  return:
  purpose:

*/
void SequenceSet::display_SS(){}


/*
  Method: validate
  param:
  return:
  purpose:

*/
void SequenceSet::validate(){}


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