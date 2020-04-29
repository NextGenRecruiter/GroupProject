/*
  Authors: Jacob Hopkins, Misky Abshir, Tyler Willard
  Date: 4/27/2020
*/
#include <iostream>
#include <list>
#include <string>
using namespace std;
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
    Block* block_head;
    Block* current_block;
  
  public:
    SequenceSet();
    ~SequenceSet();
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