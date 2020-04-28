/*
    Authors: Jacob Hopkins, Misky Abshir, and Tyler Willard
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
    std::cout << "Inita" << std::endl;
    test = SequenceSet();


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
    