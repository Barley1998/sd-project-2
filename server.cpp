// biblereader.cpp
// main function for Project 1

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include "fifo.h"
#include <stdlib.h>
using namespace std;

int main (/*int argc, char** argv*/) {
	LookupResult result = SUCCESS;
	// Create Bible object to process the raw text file
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	webBible.buildTextIndex();
	Verse verse;
	Fifo recfifo("_request");
	Fifo sendfifo("_reply");
	Ref newRef;

	recfifo.openread(); // only open once
	sendfifo.openwrite();
	string returnMessage;
	while (true) {
		returnMessage = "";
		string refStr = recfifo.recv();

		cout << refStr << endl;

		// Get book number
		string strbook = GetNextToken(refStr, ":");
		int b = atoi(strbook.c_str());
		cout << b << endl;
		// Get the chapter number
		string strchap = GetNextToken(refStr, ":");
		int c = atoi(strchap.c_str());
		cout << c << endl;
		// Get the verse number
		string strverse = GetNextToken(refStr, " ");
		int v = atoi(strverse.c_str());
		cout << v << endl;
		//Get number of verses
		int times = 1;
		if (refStr != to_string(v)) {
			string strTimes = GetNextToken(refStr, " ");
			times = atoi(strTimes.c_str());
			cout << times << endl;
		}
		
		//checks if the string parsing failed at any point
		if (b != 0 && c != 0 && v != 0) {
			
				newRef = Ref(b, c, v);
				newRef.display();
				verse = webBible.lookup(newRef, result);
				if (result != NO_BOOK && result != NO_CHAPTER && result != NO_VERSE) {
					//constructs the string to return
					returnMessage = newRef.getBookName() + ":" + to_string(c) + ":" + to_string(v) + " " + verse.getVerse();
					cout << returnMessage << endl;
					sendfifo.send(returnMessage);
					//loops nextVerse the number of times specified
					
						for (int i = 0; i < times - 1; i++) {
							Verse next = webBible.nextVerse(result);
							Ref nextRef = next.getRef();
							returnMessage = nextRef.getBookName() + ":" + to_string(nextRef.getChap()) + ":" + to_string(nextRef.getVerse()) + " " + next.getVerse() + " ";
							sendfifo.send(returnMessage);
						}
						sendfifo.send("$end");
						cout << returnMessage << endl;

					
					
				}
				else {
					//sends the error message to the client
					string errorMessage = verse.getVerse();
					cout << errorMessage << endl;
					result = SUCCESS;
					sendfifo.send(errorMessage);
					sendfifo.send("$end");
				}

				
			
		}
		else {
			//error that shows the expected format
			sendfifo.send("Invalid Format: Must be in a book-number:chapter-number:verse-number number of verses format");
			sendfifo.send("$end");
		}
		
	}
	sendfifo.fifoclose();
	recfifo.fifoclose();


}
