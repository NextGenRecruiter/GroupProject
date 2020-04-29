/*
  Authors: Jacob Hopkins, Misky Abshir, Tyler Willard
  Date: 4/27/2020
*/
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
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
    struct Block;             //see below
    struct Index;
    Block *first;
    Index *root;
    int field_count;          //count of fields per record
    int *field_offset;        //character offset per record
    int block_size;           //records per block
    int default_cap;          //where the program will fill blocks to by default
    int record_size;          //number of characters per record
    std::string in_filename;          //filename for input
    std::string out_filename;         //filename for output
    vector<int> field_sizes;  //sizes of each field

  
  public:
    SequenceSet(int f_count, int b_size, int r_size);
    SequenceSet(int f_count, int b_size, int r_size, int d_cap, std::string i_filename, std::string o_filename);
    ~SequenceSet();
    void create();
    void load();
    void close();
    bool is_open();
    int search();
    void populate();
    void insert();
    void del();
    void update();
    void display_record();
    void display_field();
    void display_file();
    void display_SS();
    void validate();
    void addIndex(int primKey, Block *b);
    void delIndex(int primKey);
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
  Block *next, *previous;
  int records_count;

  std::vector<  std::vector<char> > data; //2 dimensional vector holding all data
};

/*
  This is an index
*/
struct SequenceSet::Index {
  int key[4];
  Block *block[4];
  Index *subTree[4], *nextNode, *parent;
};