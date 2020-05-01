#!/bin/bash
	echo "----------------Sequence Set Generator---------------\c"
	echo "-----------------------------------------------------\c"
	echo "We use lowercase letters to choose an optain\c"
	echo "d: calls the delete method.\c"
	echo "i: calls the insert method.\c"
	echo "s: displays all the blocks.\c"
	echo "r: displays the record.\c"
	echo "f: displays the fields.\c"
	echo "b: displays the B+ Tree.\c"
	echo "c: creates the index file.\c"
	echo "u: calls the update method.\c"
	echo "m: will display this menu.\c"
	echo "x: will end this program.\c"
	
echo "Enter Choice\c"
		read choice;

	while [["choice"!='x']]
	do
		echo "-----------------------------------------------------\c"
		
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
			case 'x': 	echo "Terminating program, goodbye!\c"
	
	echo "-----------------------------------------------------\c"
	
done

