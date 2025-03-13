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
	ifstream in;
	string verseText = "";
	int refLocation = bibMap[ref];
	instream.open(infile, ifstream::in);
	instream.clear();
	instream.seekg(refLocation);

	getline(instream, verseText);
	

	Verse verse = Verse(verseText);
	return verse;
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

void Bible::buildTextIndex() {
	
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
	cout << "Last Offset: " << offset << endl;
}
