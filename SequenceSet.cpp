#include<iostream>
#include <cstdio>
#include <fstream>
#include "SequenceSet.h"

/*
  Here we have the default constructor for the SequenceSet

*/
SequenceSet::SequenceSet(){

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