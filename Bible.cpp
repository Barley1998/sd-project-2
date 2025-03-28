// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
	buildTextIndex();
}

// Constructor – pass bible filename
Bible::Bible(const string s) { 
	infile = s; 
	buildTextIndex();
}

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
	//Take a reference, find the byte offset with its location, move the file pointer to that location
	//then get the verse and construct a verse object
	ifstream in;
	string verseText = "";

	if (bibMap.find(ref) != bibMap.end()) {
		int refLocation = bibMap[ref];
		instream.open(infile, ifstream::in);
		instream.clear();
		instream.seekg(refLocation);

		getline(instream, verseText);


		Verse verse = Verse(verseText);
		return verse;
	}
	else {
		Ref test = Ref(ref.getBook(), 1, 1);
		Verse error;
		if (bibMap.find(test) == bibMap.end()) {
			error = Verse("1:1:1 Error, invalid book number");
			status = NO_BOOK;
			return error;
		}
		test = Ref(1, ref.getChap(), 1);
		if (bibMap.find(test) == bibMap.end()) {
			error = Verse("1:1:1 Error, invalid chapter number");
			status = NO_CHAPTER;
			return error;
		}
		test = Ref(1, 1, ref.getVerse());
		if (bibMap.find(test) == bibMap.end()) {
			error = Verse("1:1:1 Error, invalid verse number");
			status = NO_VERSE;
			return error;
		}
		return error;
	}
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	string v = "";
	Verse verse;
	if (!instream.peek() != EOF) {
		getline(instream, v);
		
		Verse verse = Verse(v);
		status = SUCCESS;
		return verse;
	}
	else { 
		status = OTHER;
	}
	verse = Verse("1:1:1 You have reached the end");
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

void Bible::buildTextIndex() {
	//Builds a map of every verse in the bible with the reference as the key to the byte offset
	ifstream in;
	string str = "";
	instream.open(infile, ifstream::in);
	int offset = instream.tellg();
	while (getline(instream, str)) {
		
		Ref newRef = Ref(str);
		bibMap.insert({ newRef, offset });
		offset = instream.tellg();

	}
	/*
	for (const auto& pair : bibMap) {
		Ref test = pair.first;
		test.display();
		cout << " " << pair.second;
	}
	*/
	
}
