/*
  Authors: Jacob Hopkins, Misky Abshir, Tyler Willard
  Date: 4/27/2020
*/
#include <iostream>
#include <list>
#include <string>

/*
  This is a datatype for handling large file in and out of RAM.
  
  We need
    - constructor(s) / destructor (etc. for in-RAM objects)
    - create
    - open/load (necessary components of an existing SS {i.e. header record & index file into memory)
        consider optionally running the validate method 
    - close
    - is_empty (via a flag, can be applied to either file, a block, a record slot in a block, or a field within a record)
    - search (for a record)
    - populate (populate the blocked record file from the input data file)
        consider populating to 3/4 capacity as a default parameter
        (can be changed for testing block merging, splitting, & record redistribution) 
    - insert (a record)
    - delete (a record)
    - update (a field of a record)
    - display_record
    - diplay_SS (parameterized to display the whole record or a subset of fields)
    - validate (is your sequence set ordered by primary key? Can you get to each record via the index file?)
    - (...private helper functions/methods)
    - (...debug functions/methods) {consider using a static debug flag for the class} 
*/
class SequenceSet
{
  private:
    struct Block;
    // Here is a doubly linked list
    std::list <Block> blocks;
  
  public:
    SequenceSet();
    int create();
    int load();
    bool is_open();
    int search();
    int populate();
    int insert();
    int remove();
    int update();
    void display_record();
    void display_SS();
    void validate();

};


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
  int fields_count;
  std::string key;
  std::list <std::string> fields;

};


/*
  Here we have the default constructor for the SequenceSet

*/
SequenceSet::SequenceSet(){

}


/*
  Method: Create
  param:
  return:
  purpose:

*/
int SequenceSet::create(){

  return 0;
}


/*
  Method: load
  param:
  return:
  purpose:

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