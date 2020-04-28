/*
  Authors: Jacob Hopkins, Misky Abshir, and Tyler Willard
  Date: 4/27/2020
*/
#include <iostream>
#include <string>
#include <list>
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
  static const int blocksize = 1500;
    // Here is a doubly linked list
    std::list <std::string> data;

    void showData(){
      std::list<std::string> :: iterator i;
      for (i = data.begin(); i != data.end() ; ++i)
        std::cout << *i << " ";
      std::cout << '\n';
    }
    struct block
		{
			block* next;
			block* prev;
			int zip[blocksize];
			string placename[blocksize];
			string state[blocksize];
			string county[blocksize];
			float latitude[blocksize];
			float longitude[blocksize];
		}typedef *blockptr;
		blockptr blockhead;
		blockptr current;

  public:
    SequenceSet();
    int create();
    bool is_open();
    void search();
    void populate();
    void insert();
    void remove();
    void update();
    void display_record();
    void display_SS();
    void validate();
    void buffer(string, blockptr, int);
	  void addzip(int, int, blockptr);
	  void addplace(string, int, blockptr);
	  void addstate(string , int, blockptr);
	  void addcounty(string, int, blockptr);
	  void addlat(float, int, blockptr);
	  void addlong(float, int, blockptr);

};
