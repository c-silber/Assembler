//
// Implementation of the Instruction Class
//

#include "stdafx.h"
#include "Instruction.h"

/**/
/*

NAME


Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)

SYNOPSIS

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
	a_buff -> contents of one line of the file

DESCRIPTION

Parses the line of the file to get the instruction type.
If the first character is a ';', the instruction type is a comment.
Otherwise:
	A comment can be contained anywhere in the file, so first check if there are any ; and remove everything after the ;
	Go through each word in the file:
		1) If the word is 'end' - return END instruction type
		2) Check if the word is an assembly language instruction (org, ds, dc)
			a. org: set m_origin
			b. ds: set m_next
			c. dc: set m_constant
		Return assembly language instruction as instruction type
		3) Check if the word is an op code
		Return machine instruction as instruction type
		4) If it's none of these, it's a label


RETURNS

InstructionType

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
{	
	// reset all previous values to default
	m_Label = "";
	m_NumOpCode = 0;
	m_Constant = 0;

	// if the beginning of the line contains a ';' entire line is a comment
	if (a_buff.at(0) == ';') {
		return Instruction::InstructionType::ST_Comment;
	}
	else {
		a_buff = a_buff.substr(0, a_buff.find(";", 0));
		istringstream iss(a_buff);
		string curr;	
		while (iss >> curr) {
			// check if we've reached the end
			if (curr == "end") {
				return Instruction::InstructionType::ST_End;
			}
			// check if it's an assembly language instruction
			else if (curr == "org" || curr == "ds" || curr == "dc") {
				m_instruction = curr;
				if (m_instruction == "org") {
					iss >> curr;
					m_origin = stoi(curr);
				}
				else if (m_instruction == "ds") {
					iss >> curr;
					m_next = stoi(curr);
				}
				else if (m_instruction == "dc") {
					iss >> curr;
					m_Constant = stoi(curr);
				}
				return Instruction::InstructionType::ST_AssemblerInstr;
			}
			// check if it's an opCode
			else if (isOpCode(curr)) {
				string newVal;
				iss >> newVal;
				if (newVal == "ds" || newVal == "dc") {
					m_Label = curr;
					iss >> newVal;
					m_Constant = stoi(newVal);
					m_NumOpCode = 0;
					m_OpCode = "";
					return Instruction::InstructionType::ST_AssemblerInstr;
				}
				m_Operand = newVal;
				return Instruction::InstructionType::ST_MachineLanguage;
			}
			// if it's none of these, it's a label
			else {
				if (m_Label == "") {
					m_Label = curr;
				}
			}
		}
	}
}

/**/
/*

NAME


bool Instruction::IsValidLabel()

SYNOPSIS

bool Instruction::IsValidLabel() - checks if the label is valid

DESCRIPTION

	Checks to make sure that the label is valid.
	If the label is > 10, it's not a valid label - return false
	If the label is not a letter, it's not valid - return false
	Otherwise, return true


RETURNS

True/False

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
bool Instruction::IsValidLabel() {
	// if the size of a label is greater than 10, return false
	if (m_Label.size() > 10) {
		return false;
	}
	// check if any of the chacters in the label is not a letter
	for (int i = 0; i < m_Label.size(); i++) {
		if (!isalpha(m_Label[i])) {
			return false;
		}
	}

	// otherwise, return true
	return true;
}

/**/
/*

NAME

bool Instruction::isOpCode(string a_value)

SYNOPSIS

bool Instruction::isOpCode(string a_value) - checks if the value is an opCode
	a_value -> string to be checked if it's an opCode

DESCRIPTION

	Run through the list of valid opcodes and if any of them match, return true

RETURNS

True/False

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
bool Instruction::isOpCode(string a_value) {
	transform(a_value.begin(), a_value.end(), a_value.begin(), ::toupper);
	string opCodes[13] = { "ADD", "SUB", "MULT", "DIV", "LOAD", "STORE", "READ", "WRITE", "B", "BM", "BZ", "BP", "HALT" };
	for (int i = 0; i < 13; i++) {
		if (a_value == opCodes[i]) {
			m_NumOpCode = i + 1;
			m_OpCode = opCodes[i];
			return true;
		}
	}
	return false;
}

/**/
/*

NAME

int Instruction::LocationNextInstruction(int a_loc)

SYNOPSIS

int Instruction::LocationNextInstruction(int a_loc) - computes the location of the next instruction

DESCRIPTION

If a_loc is 0, return the original location
If m_next isn't 0, set temp = m_next, m_next = 0 and return a_loc + temp
Otherwise, increase a_loc by 1;

RETURNS

Integer

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
int Instruction::LocationNextInstruction(int a_loc) {
	if (a_loc == 0) {
		return m_origin;
	}
	else if (m_next != 0) {
		int temp = m_next;
		m_next = 0;
		return a_loc + temp;
	}
	else {
		return a_loc + 1;
	}
}