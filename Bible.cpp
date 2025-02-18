// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
	
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line that holds ref ...
    // update the status variable
	
	
	instream.open(infile, ifstream::in);
	isOpen = true;
	

	
	status = NO_BOOK; // placeholder until retrieval is attempted
	// create and return the verse object
	Verse aVerse;
	Ref temp;
	
	string verse = "";
	bool noVerse = false;

	

	while (status != SUCCESS) {
		

		getline(instream, verse);
		string::size_type end = verse.find_first_of(" ", 0);
		string tempStr = verse.substr(0, end);
		temp = Ref(tempStr);
		
		//Checks to see if it finds a valid verse in the chapter
		
		
		
		if (temp > ref) {
			if (noVerse) {
				status = NO_VERSE;
				string s =  "Error: No such verse " + to_string(ref.getVerse()) ;
				string s2 = +" in " + ref.getBookName();
				return aVerse = Verse(s + s2);
			}
			else {
				status = NO_CHAPTER;
				string s = "Error: No such chapter " + to_string(ref.getChap());
				string s2 = " in " + ref.getBookName();

				return aVerse = Verse(s + s2);
			}
		}
		if (temp.getBook() == ref.getBook()) {
			if (temp.getChap() == ref.getChap()) {
				noVerse = true;
			}
			else noVerse = false;
		}

		//Checks if the references are equal
		if (temp == ref) {
			 return aVerse = Verse(verse);
			status = SUCCESS;

		}
	}
	
	   // default verse, to be replaced by a Verse object
	   // that is constructed from a line in the file.
	
    return aVerse;
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	string v = "";
	Verse verse;
	if (!instream.eof()) {
		if (instream.eof()) {
			status == OTHER;
			return verse;
		}
		getline(instream, v);
		
		Verse verse = Verse(v);
		status = SUCCESS;
		return verse;
	}
	else { 
		status = OTHER;
	}
	return verse;
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	if (status == NO_BOOK) {
		return "Book Not Found";
	}
	else if (status == NO_CHAPTER) {
		return "Chapter Not Found";
	}
	else if (status == NO_VERSE) {
		return "Verse Not Found";
	}
	return "Unknown Error";
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}

// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status) {
	return ref;
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) {
	return ref;
}
