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
  
  /*
    Here we declare and initialize the sequence set data. This will call load().
  */
  
  SequenceSet data;

  data.create();                //!

  data.populate();              //!

  //while(true)
  //  data.display_field();

  //data.display_record(); //works most of the time, with the occasional exit

  //data.display_file();          //this works great

  //data.display_SS();          //this works great

  //data.developer_show();      //this works great

  /*
  std::vector<int> loc = data.search(data.get_field_from_record(0,0,0));
  std::cout << "\n" << data.get_field_from_record(0,0,0) << "\nBlock:\t" << std::to_string(loc[0]) << "\nRecord:\t" << std::to_string(loc[1]) << "\n";
  loc = data.search(data.get_field_from_record(4,1,0));
  std::cout << "\n" << data.get_field_from_record(4,1,0) << "\nBlock:\t" << std::to_string(loc[0]) << "\nRecord:\t" << std::to_string(loc[1]) << "\n";
  loc = data.search(data.get_field_from_record(4,1,1));
  std::cout << "\n" << data.get_field_from_record(4,1,1) << "\nBlock:\t" << std::to_string(loc[0]) << "\nRecord:\t" << std::to_string(loc[1]) << "\n";
  loc = data.search("42.1934"); // from line 28
  std::cout << "\n42.1934" << "\nBlock:\t" << std::to_string(loc[0]) << "\nRecord:\t" << std::to_string(loc[1]) << "\n";
  loc = data.search("yeeeet"); // from line 28
  std::cout << "\nyeeeet" << "\nBlock:\t" << std::to_string(loc[0]) << "\nRecord:\t" << std::to_string(loc[1]) << "\n";
  */

  //data.insert("");

  /*
  data.update(0,0,0,"12345");
  data.update(0,0,1,"12345");
  data.update(0,0,2,"12345");
  data.update(0,0,3,"12345");
  data.update(0,0,4," 12.345");
  data.update(0,0,5,"-12.345");
  */


  //data.display_SS();
  //data.validate();



  //! show of arguments and example using them
  //std::cout << "You have entered " << arg_count << " arguments:" << "\n";
  //for (int i = 0; i < arg_count; ++i) 
  //    std::cout << arg_values[i] << "\n";

  if(*arg_values[1] == 'a'){
    std::cout << "Finding the furthest zip codes in: " << arg_values[2] << "\n";
    data.nsew_most(arg_values[2]);
  }

  if(*arg_values[1] == 'b'){
    std::cout << "Finding the State and Place name of zip code: " << arg_values[2] << "\n";
    for(int i = 2; i < arg_count; i++){
      data.state_and_place_from_zip(arg_values[i]);
    }
  }

  //forbiden code here
  //wait for character so the screen does not disappear
  std::cout << "Press enter...";
  getchar();

  //return that the program ran correctly
  return 0;
}
