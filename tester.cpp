#include <iostream>
#include <string>
#include "SequenceSet.cpp"
using namespace std;

void menu(){
	cout<<"----------------Sequence Set Generator---------------"<<endl<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	cout << "We use lowercase letters to choose an optain" << endl;
	cout << "d: calls the delete method." << endl;
	cout << "i: calls the insert method." << endl;
	cout << "s: displays all the blocks." << endl;
	cout << "r: displays the record." << endl;
	cout << "f: displays the fields." << endl;
	cout << "b: displays the B+ Tree." << endl;
	cout << "c: creates the index file." << endl;
	cout << "u: calls the update method." << endl;
	cout << "m: will display this menu." << endl;
	cout << "x: will end this program." << endl;
	
}

int main()
{
	SequenceSet s;
	char choice =' ';
	
	s.populate();
	menu();
	while(choice!='x'){
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"Enter Choice"<<endl;
		cin >> choice;
		switch(choice){
		
			case 'd':	s.delete_record(),
						s.create();
						break;
			case 'm':	menu();
						
						break;
			case 'r': 	s.display_record();
						break;
			case 'f': 	s.display_field();
						break;
			case 's': 	s.display_SS();
						break;
			case 'i': 	s.insert(),
						s.create();
						break;
			case 'b':	b.print();
						break;
			case 'c': 	s.create();
						break;
			case 'u': 	s.update();
						break;
			case 'x': 	cout << "Terminating program, goodbye!" << endl;
		}
	}
	cout<<"-----------------------------------------------------"<<endl<<endl;

    return 0;
	
}