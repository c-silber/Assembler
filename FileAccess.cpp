//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/**/
/*

NAME

FileAccess::FileAccess(int argc, char *argv[])

SYNOPSIS

FileAccess::FileAccess(int argc, char *argv[])
	argc	-> how many files (should be 20)
	argv[]	-> array containing the names of the files

DESCRIPTION

Constructor for the file access class. Makes sure that there are only 2 parameters and that the files can be opened.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}
	// Open the file.  One might question if this is the best place to open the file.
	// One might also question whether we need a file access class.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated."
			<< endl;
		exit(1);
	}
}
FileAccess::~FileAccess()
{
	m_sfile.close();
}

/**/
/*

NAME

FileAccess::GetNextLine(string &a_buff)

SYNOPSIS

bool FileAccess::GetNextLine(string &a_buff)
	a_buff -> contents of one line in the file

DESCRIPTION

Writes the contents of the next line in the file to a_buff

RETURNS

True/False

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof()) {

		return false;
	}
	getline(m_sfile, a_buff);

	// Return indicating success.
	return true;
}

/**/
/*

NAME

void FileAccess::rewind()

SYNOPSIS

void FileAccess::rewind()

DESCRIPTION

Rewinds the file so it can be read again

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void FileAccess::rewind()
{
	// Clean tall file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}
