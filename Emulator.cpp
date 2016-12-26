//
// Implementation of the Emulator Class 
//

#include "stdafx.h"
#include "Emulator.h"


/**/
/*
emulator::insertMemory(int a_location, int a_contents)

NAME

emulator::insertMemory - inserts the contents into the specified memory location

SYNOPSIS

emulator::insertMemory(int a_location, int a_contents)
	
	a_location -> the location of the contents 
	a_contents -> the actual contents to be stored at the specified location

DESCRIPTION

The purpose of this function is to insert the contents into memory so that it can later be read by the emulator. 
The function first checks that the location does not exceed the bounds of the memory. If it does, it throws an out of bounds error and
returns false.
Otherwise, the contents are stored. The first location is stored in m_origin

RETURNS

True/False - True if contents are saved successfully.

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
bool emulator::insertMemory(int a_location, int a_contents) {
	// check if the location is greater than 1000. If it is, report an out of bounds error
	if (a_location < 1000) {
		m_memory[a_location] = a_contents;
	}
	else {
		cout << "Out of bounds memory" << endl;
		return false;
	}

	// check if the contents are not blank and if m_isFirst is set to true
	if (a_contents != 0 && m_isFirst) {
		// set the original location to a_location
		m_origin = a_location;
		// set m_isFirst to false so that we don't do this again
		m_isFirst = false;
	}

	return true;
}

/**/
/*
emulator::runProgram()

NAME

emulator::runProgram - inserts the contents into the specified memory location

SYNOPSIS

void emulator::runProgram()

DESCRIPTION

The purpose of this function is to actually run the emulator. The emulator will continue to run until the m_terminate variable is set to true. 
(This will happen when the program reaches a "HALT" instruction) 
The function begins a loop that gets the op code from the current memory location. There is then a switch statement on the op code which calls it's 
own function to actually do the calculations for that instruction.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::runProgram() {

	m_loc = m_origin;

	// continue the loop until the m_terminate variable is set to true
	while (!m_terminate) {
		m_instruction.first = m_memory[m_loc] / 10000;
		m_instruction.second = m_memory[m_loc] % 10000;

		// if it's the first instruction, increase m_loc and continue the loop
		if (m_instruction.first == 0) {
			m_loc++;
			continue;
		}

		// switch case for the opCodes
		switch (m_instruction.first) {
		case 1:
			Add();
			break;
		case 2:
			Sub();
			break;
		case 3:
			Mult();
			break;
		case 4:
			Div();
			break;
		case 5:
			Load();
			break;
		case 6:
			Store();
			break;
		case 7:
			Read();
			break;
		case 8:
			Write();
			break;
		case 9:
			Branch();
			break;
		case 10:
			Bm();
			break;
		case 11:
			Bz();
			break;
		case 12:
			Bp();
			break;
		case 13:
			Halt();
			break;
		default:
			m_loc++;
		}
	}
}

/** /
/*
NAME

emulator::Add

SYNOPSIS

void emulator::Add()

DESCRIPTION

The purpose of this function is to perform the add instruction. The sum is first checked to make sure there is no overflow error.
If there isn't the sum is added to the accumulator. The location is then incremented.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Add()
{
	// compute the sum
	int a_sum = accumulator + m_memory[m_instruction.second];
	// check for overflow error
	if (a_sum > 999999) {
		// report the error and terminate
		cout << "Overflow error. Program terminating " << endl;
		exit(1);
	}
	accumulator = a_sum;
	m_loc++;

}

/** /
/*
NAME

emulator::Sub

SYNOPSIS

void emulator::Sub()

DESCRIPTION

The purpose of this function is to perform the subtraction instruction. The sum is first checked to make sure there is no overflow error.
If there isn't the sum is added to the accumulator. The location is then incremented.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Sub()
{
	int a_sum = accumulator - m_memory[m_instruction.second];
	// check for overflow error
	if (a_sum < -999999) {
		// report the error and terminate
		cout << "Error: Overflow - Program terminating" << endl;
		exit(1);
	}
	accumulator = a_sum;
	m_loc++;

}

/** /
/*
NAME

emulator::Mult

SYNOPSIS

void emulator::Mult()

DESCRIPTION

The purpose of this function is to perform the multiplication instruction. The product is first checked to make sure there is no overflow error.
If there isn't the product is added to the accumulator. The location is then incremented.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Mult()
{
	int prod = accumulator * m_memory[m_instruction.second];
	// check for overflow error
	if (prod > 999999 || prod < -999999) {
		// report the error and terminate
		cout << "Error: Overflow - Program terminating" << endl;
		exit(1);
	}
	accumulator = prod;
	m_loc++;
}


/** /
/*
NAME

emulator::Div

SYNOPSIS

void emulator::Div()

DESCRIPTION

The purpose of this function is to perform the division instruction. The second instruction is first checked to make sure it is not zero and won't
crash the program because of a division by zero error. If it's not zero, the result of the division instruction is added to the accumulator.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Div()
{
	// check if the second instruction is 0, throw a division by zero error
	if (m_instruction.second == 0) {
		cout << "Error: Division by zero - Program terminating" << endl;
		exit(1);
	}
	accumulator = accumulator / m_memory[m_instruction.second];
	m_loc++;
}


/** /
/*
NAME

emulator::Load

SYNOPSIS

void emulator::Load()

DESCRIPTION

The purpose of this function is to perform the load instruction. It adds the contents of the address to the accumulator.
The location is then incremented.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Load()
{
	// set the accumulator equal to the second memory instruction pair
	accumulator = m_memory[m_instruction.second];
	m_loc++;
}

/** /
/*
NAME

emulator::Store

SYNOPSIS

void emulator::Store()

DESCRIPTION

The purpose of this function is to perform the store instruction. It stores the contents of the accumulator at the specified location.
The location is then incremented.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Store()
{
	// store the value of the accumulator in the second memory instruction pair
	m_memory[m_instruction.second] = accumulator;
	m_loc++;
}


/** /
/*
NAME

emulator::Branch

SYNOPSIS

void emulator::Branch()

DESCRIPTION

The purpose of this function is to perform the branch instruction. 
It makes the location the same as the operand causing the program to "jump" to that loaction.


RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Branch() {
	// set the location to the second memory instruction pair
	m_loc = m_instruction.second;
}

/** /
/*
NAME

emulator::Bm

SYNOPSIS

void emulator::Bm()

DESCRIPTION

The purpose of this function is to perform the bm instruction.
If the accumulator is a negative number, perform a regular branch. Otherwise, just increase the memory location


RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Bm()
{
	// check if the accumulator is less than 0 and set the location equal to the second memory insrtuction pair
	if (accumulator < 0)
		m_loc = m_instruction.second;
	// otherwise, increase the location
	else {
		m_loc++;
	}
}

/** /
/*
NAME

emulator::Bz

SYNOPSIS

void emulator::Bz()

DESCRIPTION

The purpose of this function is to perform the bz instruction.
If the accumulator is equal to zero, perform a regular branch instruction.
Otherwise increase the memory location


RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Bz(){
	// check if the accumulator is equal to 0
	if (accumulator == 0) {
		// set the location equals to the second memory instruction pair
		m_loc = m_instruction.second;
	}
	// otherwise increase the location
	else {
		m_loc++;
	}
}

/** /
/*
NAME

emulator::Bp

SYNOPSIS

void emulator::Bp()

DESCRIPTION

The purpose of this function is to perform the bp instruction.
Checks if the accumulator is greater than 0. If it is, branch to that memory location. Otherwise, increase the location.


RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Bp(){
	// check if the accumulator is greater than 0
	if (accumulator > 0) {
		// set the memory location equal to the second memory instruction pair
		m_loc = m_instruction.second;
	}
	else {
		// otherwise, increase the location
		m_loc++;
	}

}

/** /
/*
NAME

emulator::Read

SYNOPSIS

void emulator::Read()

DESCRIPTION

The purpose of this function is to perform the read instruction.
The user is asked to enter an input. The input size needs to be <=6, so if it's greater it is just trimmed down.
There is a then a try/catch block to make sure that the uesr only entered a numeric input. If the input is not numeric,
the read() function is called recursively. Otherwise, the memory location is increased.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Read()
{
	string input;

	// prompt the user for input
	cout << "? ";
	cin >> input;


	// if the input size if greater than 6, trim it down to only 6 
	if (input.size() > 6) {
		input.erase(6, input.size());
	}

	int numInput;

	// make sure that the input is numeric. 
	try {
		// try to convert the number to an integer
		numInput = stoi(input);
		// store it in the second memory instruction location
		m_memory[m_instruction.second] = numInput;
		m_loc++;
	}
	catch (invalid_argument& e) {
		cout << "Invalid Input. Try again" << endl;
		// If input is invalid, ask the user again.
		Read();
	}

}

/** /
/*
NAME

emulator::Write

SYNOPSIS

void emulator::Write()

DESCRIPTION

The purpose of this function is to perform the write instruction.
Simply prints out whatever is in memory. The memory location is increased.


RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Write() {
	// write the value stored in the second memory instruction to the screen
	cout << to_string(m_memory[m_instruction.second]) << endl;
	m_loc++;
}

/** /
/*
NAME

emulator::Halt

SYNOPSIS

void emulator::Halt()

DESCRIPTION

The purpose of this function is to perform the halt instruction.
Sets m_terminate to true.


RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void emulator::Halt() {
	// set the m_terminate variable to true to stop the loop from reiterating
	m_terminate = true;
}
