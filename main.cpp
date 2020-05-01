/*
  Authors: Jacob Hopkins, Misky Abshir, and Tyler Willard
  Date: 4/27/2020
  Due: 5/1/2020
  
  TODO:
    - Create SequenceSet Class in the 'SequenceSet.h' file
    - Create a test driver for the class above
    - Create the program for using the txt files with the class
    - Create the design doccument for
        - The Class
        - The Test Driver
    - A User Manual
    - DyOxygen the Code
    
 Specifications for a program which uses the Sequence Set class:
    The application program will iterate through the sequence set displaying (neatly)
    the Northernmost, Southernmost, Easternmost, and Westernmost zip code for a specified state.
    {You can verify the results by sorting the Excel source data file first by state, then by longitude or by latitude}

    Also, the application program, using a different set of command line flags,
    will display (neatly) the State and Place Name for a specified Zip Code (or set of Zip Codes).

    Run the test driver program to build the full Sequence Set file (and index file);
    Run the application program specifying the Sequence Set file and the State on the command line;
    Use the Unix script command to show:
        the building of the Sequence Set file,
        the repeated running of the application program and its output for several states,
        the repeated running the application program to display the State and Place Name for several Zip Codes. 


  In Video 4:
  14:30

  I don't mind phone call for audi as well, 612-707-2182 that's my cellphone
*/


//import header with the SequenceSet class
#include "SequenceSet.cpp"
#include <cstdio>

/*
  Here is the main function to start the program.
*/
int main(int arg_count, char** arg_values){

  //show of arguments and example using them
  //std::cout << "You have entered " << arg_count << " arguments:" << "\n";
  //for (int i = 0; i < arg_count; ++i) 
  //    std::cout << arg_values[i] << "\n";


  /*
    Here we declare and initialize the sequence set data. This will call load().
  */
  SequenceSet data;
  
  data.create();                //this works great
  data.populate();              //this works great
  while(true)
    data.display_field();
  //data.display_record(); //works most of the time, with the occasional exit
  //data.display_file();          //this works great
  //data.display_SS();          //this works great
  //data.developer_show();      //this works great

  //forbiden code here
  //wait for character so the screen does not disappear
  std::cout << "Press enter...";
  getchar();

  //return that the program ran correctly
  return 0;
}
