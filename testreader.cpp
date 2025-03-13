// biblereader.cpp
// main function for Project 1

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main (int argc, char **argv) {
	// Create Bible object to process the raw text file
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
/*	Ref ref1 = Ref(1, 1, 1);
	Ref ref2 = Ref(1, 1, 3);
	Ref ref3 = Ref(1, 1, 5);
	cout << "Number of References Created: " << webBible.bibMap.size() << endl;
	cout << webBible.bibMap[ref1] << webBible.bibMap[ref2] << webBible.bibMap[ref3];
	*/
	Verse verse;
	int b, c, v;
	LookupResult result;
	cout << "Using Bible from: ";
	webBible.display();
	
	// Prompt for input: get reference to lookup
	// This is good for testing your classes quickly for the first milestone.
	/* cout << "Enter 3 integers for book, chapter and verse to find: " << flush;
	cin >> b >> c >> v;*/
	// TODO: your final program should get input from command line arguments instead.
	
	int times = 1;
	if (argc > 3 && argc < 6) {
		if (argc == 5) {
			b = atoi(argv[1]);
			c = atoi(argv[2]);
			v = atoi(argv[3]);
			times = atoi(argv[4]);
		}
		else  {
			b = atoi(argv[1]);
			c = atoi(argv[2]);
			v = atoi(argv[3]);
		}
	}
	else if(argc != 1){
		cout << "INVALID NUMBER OF ARGUMENTS" << endl;
	}
	// Create a reference from the numbers
	Ref ref(b, c, v);
	
	// Use the Bible object to retrieve the verse by reference
	
	if (argc == 1) {
		cout << "ERROR: NO ARGUMENTS" << endl;
	}
	else if (argc > 3 && argc < 6){

		if (b <= 66 && b > 0) {
			cout << "Looking up reference: ";
			ref.display();
			cout << endl;

			verse = webBible.lookup(ref, result);
			//cout << "Result status: " << result << endl;
			verse.display();
			cout << endl;
			for (int i = 0; i < times - 1; i++) {
				verse = webBible.nextVerse(result);
				verse.display();
				cout << endl;
			}
			
		}
		else { cout << "Error: no book " << b << " in the bible" << endl; }
	}
	
}
