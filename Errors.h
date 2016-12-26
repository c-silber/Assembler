//
// Class to manage error reporting.
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:

	// Records an error message.
	static void RecordError(string &a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	// returns true if there are no errors
	bool isEmpty();

};
#endif