#include<iostream>
#include <cstdio>
#include <fstream>
#include "SequenceSet.h"

int SequenceSet::create(){


}



/*
  Here we create a Block

  block size {default to (512B / block)} 

Each active block should include the following components:
    count of records ( > 0 )
    pointers to preceding & succeeding active blocks
    set of records ordered by key 

Each avail block should include the following components:
    count of records ( == 0 )
    pointer to succeeding avail block 

*/
struct SequenceSet::Block {
  //data parts
  struct Record;
  std::list<Record> records;

  int block_size;
  int record_count;
  int* next_block;
  int* prev_block;
  
  //constructors
  Block() : block_size(512) {}   //look, a constructor
  
  //methods
  int get_block_size() { 
    return block_size; 
  }

};

/*
  Here we create a Record

  A Block default size is 512
*/
struct SequenceSet::Block::Record{
  struct Field;
  std::list <Field> fields;
  
  int fields_count;
  std::string key;


};

struct SequenceSet::Block::Record::Field{
  std::string description;
  std::string value;
};


/*
  Here we have the default constructor for the SequenceSet

*/
SequenceSet::SequenceSet(){
    //The pointers poiting to the head and current 
    //block are pointing to nothing
    blockHead = NULL;
    currentBlock = NULL;

}

/*
  Here we have the default destructor for the SequenceSet

*/
SequenceSet::~SequenceSet(){
  delete &blocks;
}


/*
  Method: Create
  param:
  return:
  purpose:
  here we take the data file and create the sequence set file

*/
int SequenceSet::create(){
    ofstream index;

    index.open("US-Postal-Codes");
    current = blockHead;
    do{

    }
  return 0;
}


/*
  Method: load
  param:
  return:
  purpose:
  here we load blocks from the sequence set file into ram
*/
int SequenceSet::load(){

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
int SequenceSet::populate(){

  return 0;
}


/*
  Method: insert
  param:
  return:
  purpose:

*/
int SequenceSet::insert(){

  return 0;
}


/*
  Method: remove
  param:
  return:
  purpose:

*/
int SequenceSet::remove(){

  return 0;
}


/*
  Method: update
  param:
  return:
  purpose:

*/
int SequenceSet::update(){

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