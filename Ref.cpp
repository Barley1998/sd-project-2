// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <string>
using namespace std;

void Ref::makeMap() {
bibleMap[1] = "Genesis";
bibleMap[2] = "Exodus";
bibleMap[3] = "Leviticus";
bibleMap[4] = "Numbers";
bibleMap[5] = "Deuteronomy";
bibleMap[6] = "Joshua";
bibleMap[7] = "Judges";
bibleMap[8] = "Ruth";
bibleMap[9] = "1 Samuel";
bibleMap[10] = "2 Samuel";
bibleMap[11] = "1 Kings";
bibleMap[12] = "2 Kings";
bibleMap[13] = "1 Chronicles";
bibleMap[14] = "2 Chronicles";
bibleMap[15] = "Exra";
bibleMap[16] = "Nehemiah";
bibleMap[17] = "Esther";
bibleMap[18] = "Job";
bibleMap[19] = "Psalms";
bibleMap[20] = "Proverbs";
bibleMap[21] = "Ecclesiastes";
bibleMap[22] = "Song of Solomon";
bibleMap[23] = "Isaiah";
bibleMap[24] = "Jeremiah";
bibleMap[25] = "Lamentations";
bibleMap[26] = "Ezekiel";
bibleMap[27] = "Daniel";
bibleMap[28] = "Hosea";
bibleMap[29] = "Joel";
bibleMap[30] = "Amos";
bibleMap[31] = "Obadiah";
bibleMap[32] = "Jonah";
bibleMap[33] = "Micah";
bibleMap[34] = "Nahum";
bibleMap[35] = "Habakkuk";
bibleMap[36] = "Zephaniah";
bibleMap[37] = "Haggai";
bibleMap[38] = "Zechariah";
bibleMap[39] = "Malachi";
bibleMap[40] = "Matthew";
bibleMap[41] = "Mark";
bibleMap[42] = "Luke";
bibleMap[43] = "John";
bibleMap[44] = "Acts";
bibleMap[45] = "Romans";
bibleMap[46] = "1 Corinthians";
bibleMap[47] = "2 Corinthians";
bibleMap[48] = "Galatians";
bibleMap[49] = "Ephesians";
bibleMap[50] = "Philippians";
bibleMap[51] = "Colossians";
bibleMap[52] = "1 Thessalonians";
bibleMap[53] = "2 Thessalonians";
bibleMap[54] = "1 Timothy";
bibleMap[55] = "2 Timothy";
bibleMap[56] = "Titus";
bibleMap[57] = "Philemon";
bibleMap[58] = "Hebrews";
bibleMap[59] = "James";
bibleMap[60] = "1 Peter";
bibleMap[61] = "2 Peter";
bibleMap[62] = "1 John";
bibleMap[63] = "2 John";
bibleMap[64] = "3 John";
bibleMap[65] = "Jude";
bibleMap[66] = "Revelation";
}

// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)

string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { 
    makeMap();
    // Parse constructor - receives a line "34:5:7 text"
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
    
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
    makeMap();
	book = b;
	chap = c;
	verse = v;
}

string Ref::getBookName() {
    return bibleMap[book];
}

// Accessors
int Ref::getBook() {return book;}	 // Access book number
int Ref::getChap() {return chap;}	 // Access chapter number
int Ref::getVerse() {return verse;}; // Access verse number

// TO DO: implement comparison functions
// REQUIRED: == comparison
bool Ref::operator==(const Ref r) { 
    if (book == r.book && chap == r.chap && verse == r.verse) {
        return true;
    }
    else return false;
}

bool Ref::operator<(const Ref r) {
    if (book < r.book) {
        return true;
    }
    else if (book == r.book) {
        if (chap < r.chap) {
            return true;
        }
    }
    else if (book == r.book && chap == r.chap) {
        if (verse < r.verse) {
            return true;
        }
    }
    return false;
}

bool Ref::operator>(const Ref r) {
    if (book > r.book) {
        return true;
    }
    else if (book == r.book) {
        if (chap > r.chap) {
            return true;
        }
    }
    else if (book == r.book && chap == r.chap) {
        if (verse > r.verse) {
            return true;
        }
    }
    return false;
}


// NOT OPTIONAL: define < and > comparisons


// TO DO: modify display function to show book name instead of book number
void Ref::display() { 	// Display Reference
     
    if (chap != 0 && verse != 0) {
        cout << bibleMap[book] << ":" << chap << ":" << verse;
    }
}
