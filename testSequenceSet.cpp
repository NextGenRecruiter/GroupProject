/*
    Authors: Jacob Hopkins, Misky Abshir, and Tyler Willard
    Date: 4/27/2020

    testSequenceSet.cpp
    This is a test program.
    
    Sequence set is a class to handle reading data into and out of files and processing with performance.

    This program is to show the functionality of the SequenceSet class found in 'SequenceSet.h'

    In video 4:
    14:20
    
*/

#include<iostream>
#include <cstdio>
#include "SequenceSet.h"

/*
    Here is the main function of the test driver.
*/
int main(int arg_count = 0, char** arg_values = {}){

    //show of arguments and example using them
    std::cout << "You have entered " << arg_count << " arguments:" << "\n";
    for (int i = 0; i < arg_count; ++i) 
        std::cout << arg_values[i] << "\n";


    //introduction
    std::cout << "This is the test program for the SequenceSet class. " << std::endl;


    /*
        Here we declare a SequenceSet named test.
    */
    std::cout << "Declaring SequenceSet: test" << std::endl;
    SequenceSet test;
    std::cout << "Declaring SequenceSet complete." << std::endl << std::endl;
    

    /*
        Here we initialize the sequence set test.
    */
    std::cout << "Initalizing test" << std::endl;
    test = SequenceSet();
    std::cout << "test initalization complete." << std::endl << std::endl;

    /*

    */
    std::cout << "" << std::endl;
    
    std::cout << " complete." << std::endl << std::endl;
    
    
    
    //forbiden code here
    //wait for character so the screen does not disappear
    getchar();

    //return that the program ran correctly
    return 0;
}
    