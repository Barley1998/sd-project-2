/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "fifo.h"
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";
  
  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

  // Convert and check input data

  //Checks if a valid book was inserted
  /*
  bool validBook = false;
  if (book != cgi.getElements().end()) {
	  int bookNum = book->getIntegerValue();
	  if (bookNum > 66) {
		  cout << "<p>The book number (" << bookNum << ") is too high.</p>" << endl;
	  }
	  else if (bookNum <= 0) {
		  cout << "<p>The book must be a positive number.</p>" << endl;
	  }
	  else
		  validBook = true;
  }
  bool validChap = false;
  if (chapter != cgi.getElements().end()) {
	  int chapNum = chapter->getIntegerValue();
	  if (chapNum > 150) {
		  cout << "<p>The chapter number (" << chapNum << ") is too high.</p>" << endl;
	  }
	  else if (chapNum <= 0) {
		  cout << "<p>The chapter must be a positive number.</p>" << endl;
	  }
	  else
		  validChap = true;
  }
  bool validVerse = false;
  if (verse != cgi.getElements().end()) {
	  int verseNum = verse->getIntegerValue();
	  if (verseNum > 176) {
		  cout << "<p>The verse number (" << verseNum << ") is too high.</p>" << endl;
	  }
	  else if (verseNum <= 0) {
		  cout << "<p>The verse must be a positive number.</p>" << endl;
	  }
	  else
		  validVerse = true;
  }
  
  */

  /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */


  //Looks up the requested verse(s) and concatenates them to a string to later be printed
  string verseContent = "";
  Fifo recfifo("_reply");
  Fifo sendfifo("_request");
  if (validBook && validChap && validVerse) {
	  int bk = book->getIntegerValue();
	  int chap = chapter->getIntegerValue();
	  int vrs = verse->getIntegerValue();
	  int numVer = nv->getIntegerValue();
	  string serverCall = "";
	  //Constructs the string to send to the server
	  serverCall = to_string(bk) + ":" + to_string(chap) + ":" + to_string(vrs) + " " + to_string(numVer);
	  sendfifo.send(serverCall);
	  


  }
  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */

	//prints out the result from the server
	  cout << "<p>" << recfifo.recv() << "</p>" << endl;

	
	
  return 0;
}
