// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
#include <string>
using namespace std;



Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	// use Ref constructor to create verseRef
	// store the remainder of the string in verseText
    verseRef = Ref(s);
    string::size_type start = s.find_first_of(" ", 0);
    verseText = s.substr(start + 1);
    
}  	

// REQUIRED: Accessors
string Verse::getVerse() {
    return verseText;
}

Ref Verse::getRef() {
    return verseRef;
}

// display reference and verse
void Verse::display() {
    verseRef.display();
    if (verseText != " Not Found") {
        cout << " " << verseText;
    }
    
    
 }
