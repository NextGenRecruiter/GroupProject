/*
    Authors: Jacob Hopkins
    Date: 4/27/2020

    testSequenceSet.cpp
    This is a test program.
    
    Sequence set is a class to handle reading data into and out of files and processing with performance.

    This program is to show the functionality of the SequenceSet class found in 'SequenceSet.h'
*/

#include<iostream>
#include <cstdio>
#include "SequenceSet.h"

/*
    Here is the main function of the test driver.
*/
int main(){
    SequenceSet test;
    
    test = new SequenceSet();
    
    std::cout << "This is the test program for the SequenceSet class. ";
    std::getchar();
    return 0;
}
