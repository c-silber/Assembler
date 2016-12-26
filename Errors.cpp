#include "stdafx.h"
#include "Errors.h"


static vector<string> m_ErrorMsgs;

/** /
/*
NAME

Errors::RecordError(string &a_emsg)

SYNOPSIS

void Errors::RecordError(string &a_emsg)
	a_emsg -> the message to be stored with the error
		

DESCRIPTION

Adds the errors message to the vector of error messages

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void Errors::RecordError(string &a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}

/** /
/*
NAME

Errors::DisplayErrors()

SYNOPSIS

void Errors::DisplayErrors()


DESCRIPTION

Prints a list of all the errors.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void Errors::DisplayErrors() {
	cout << "--------------------------" << endl;
	cout << "Error Report" << endl;
	if (m_ErrorMsgs.size() == 1) {
		cout << "There is 1 error" << endl;
	}
	else {
		cout << "There are " + to_string(m_ErrorMsgs.size()) + " errors" << endl;
	}

	for (int i = 0; i < m_ErrorMsgs.size(); i++) {
		cout << m_ErrorMsgs[i] << endl;
	}
}

/** /
/*
NAME

Errors::isEmpty()

SYNOPSIS

bool Errors::isEmpty()


DESCRIPTION

Checks if the error message vector is empty and returns true if it is

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
bool Errors::isEmpty() {
	if (m_ErrorMsgs.size() == 0) {
		return true;
	}
	return false;
}