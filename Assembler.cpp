//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develop this project.
Assembler::~Assembler()
{
}

/**/
/*
Assembler::Pass1()

NAME

	Assembler::Pass1 - initial run through of the file to establish the locations of the symbols

SYNOPSIS

	void Assembler::Pass1();

DESCRIPTION

	This function does the initial run through of the file and establishes the locations of the symbols. Each line of the file is succcessvily analyzed 
	to get the Instruction Type. Machine language instructions and assembly instructions (containing labels) are added to the symbol table. The location
	the next instruction is computed

RETURNS

	None

AUTHOR

	Caroline Silber

DATE

	12/12/2016

*/
/**/
void Assembler::PassI()
{
	int loc = 0;
	// Tracks the location of the instructions to be generated.

	// Successively process each line of source code.
	while (true) {

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) {

			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}

		// if the line is completely blank, just continue
		if (buff == "") continue;

		// Parse the line and get the instruction type
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel()) {

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
Assembler::Pass2()

NAME

Assembler::Pass2 - second run through of the file to do the translation of the program.

SYNOPSIS

void Assembler::Pass2();

DESCRIPTION

This function does the second run through of the original file. This time through, the contents of the program are stored to a vector of a struct containing the 
translation. In addition, various error are checked on the second pass including:
	1) Checking if the memory is exceeded
	2) Checking if the end statement is missing
	3) Checking if the program continues after the end statement
	4) Checking if a label is invalid
	5) Checking if the symbol was multiply defined

If any of the above errors are found, they are stored in the error class and reported before the emulator is run

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void Assembler::PassII()
{

	int loc = 0;		// Tracks the locations of the instructions to be generated
	m_facc.rewind();	// Start at the beginning of the file

	bool exceedsMem = false, endInst = false;


	// Successively process each line of source code.
	while (true) {

		if (loc > 9999) {
			exceedsMem = true;
		}

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) {

			// If there are no more lines, we are missing an end statement.
			// Error will be reported further down
			break;
		}

		// if the line is completely blank, just continue
		if (buff == "") continue;

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		if (st == Instruction::ST_End) {
			// there is an end instruction, so setting endInst to true
			endInst = true;
			// Make sure that there is no code after the end statement
			while (m_facc.GetNextLine(buff)) {
				istringstream iss(buff);
				string character;
				while (iss >> character) {
					if (character != "\t" || character != "\n" || character != " ") {
						// record the error
						string err = "Error: Program continues after end statement";
						m_err.RecordError(err);
						// report the error
						cerr << err << endl;
						break;
					}
				}
			}
			break;
		}

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st == Instruction::ST_Comment) {
			trans t;
			t.location = 0;
			t.contents = "";
			t.org = buff;
			translationVect.push_back(t);
			continue;
		}

		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}

		// compute the location
		string contents = m_inst.getOpCode();
		if (m_symtab.getLocation(m_inst.GetOperand()) != 0){
			contents += to_string(m_symtab.getLocation(m_inst.GetOperand()));
		}

		// if there is a constant value, get that value
		if (m_inst.getConstant() != 0) {
			contents += to_string(m_inst.getConstant());
			// if the length of the string is less than 6, padd with 0s
			if (contents.length() < 6) {
				int size = contents.length();
				for (int i = 0; i < 6 - size; i++) {
					contents.insert(0, "0");
				}
			}
		}
		else if (m_inst.getConstant() == 0 && m_symtab.getLocation(m_inst.GetOperand()) == 0) {
			contents += "000";
		}

		// check if contents is just 0.
		bool zero = true;
		for (int i = 0; i < contents.length(); i++) {
			if (contents[i] != '0') {
				zero = false;
			}
		}

		// if the line is just zero, just print a blank line
		if (zero) {
			contents = "";
		}

		// store everything in the translation struct
		trans t;
		t.location = loc;
		t.contents = contents;
		t.org = buff;

		// store the contents of the struct in the vector
		translationVect.push_back(t);

		// check if the label is valid
		if (!m_inst.IsValidLabel()) {
			string err = "Error: Label is invalid";
			m_err.RecordError(err);
			// report the error
			cerr << err << endl;
		}

		// check if the symbol was multiple defined
		if (m_symtab.isMultiplyDefined(m_inst.GetLabel())) {
			// record the error
			string err = "Error: Symbol is multiple defined";
			m_err.RecordError(err);
			// report the error
			cerr << err << endl;
		}

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}

	// check if the memory allotment has been exceeded
	if (exceedsMem) {
		string err = "Error: Program exceeds memory";
		m_err.RecordError(err);
		// report the error
		cerr << err << endl;
	}

	// if endInst is false, there was no end statement in the file
	// Record the error
	if (!endInst) {
		// record the error
		string err = "Error: No end statement in the program";
		m_err.RecordError(err);
		// report the error
		cerr << err << endl;
	}

	PrintTranslation();
}

/**/
/*
Assembler::PrintTranslation()

NAME

Assembler::PrintTranslation - prints the translation of the program

SYNOPSIS

void Assembler::PrintTranslation();

DESCRIPTION

This function just prints the translation that is generated in Pass2. It goes through the vector of structs and prints out the location,
the contents, and the original statement

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void Assembler::PrintTranslation() {
	cout << "Translation of Program" << endl;

	cout << "Location" << setw(15) << "Contents" << setw(25) << "Original Statement" << endl;
	for (int i = 0; i < translationVect.size(); i++) {
		if (translationVect[i].location == 0) {
			cout << "		 ";
		}
		else {
			cout << " " << translationVect[i].location << "		";
		}
		cout << translationVect[i].contents << "	     ";
		cout << translationVect[i].org << left << endl;

	}
	cout << "----------------------------------------------" << endl;
}

/**/
/*
Assembler::RunEmulator()

NAME

Assembler::RunEmulator - begins the emulator

SYNOPSIS

void Assembler::RunEmulator();

DESCRIPTION

The purpose of this function is to begin running the emulator. Before the emulator is run, the program checks to make sure that there are no errors in the error
class. If there are any errors, the function reports that there is an error and stops running the program. If there are no errors, the function will insert the 
contents of the translation vector into the emulator and then calls the runProgram, which will actually run the emulator.

RETURNS

None

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void Assembler::RunEmulator() {
	// Stop the program if there are any errors
	if (!m_err.isEmpty()) {
		cout << "Cannot run emulation due to errors" << endl;
		m_err.DisplayErrors();
	}
	else {
		cout << "Results from emulating program" << endl;

		for (int i = 0; i < translationVect.size(); i++) {
			if (translationVect[i].location != 0) {
				int contents;
				if (translationVect[i].contents != "") {
					contents = stoi(translationVect[i].contents);
				} else {
					contents = 0;
				}
				int loc = translationVect[i].location;
				m_emul.insertMemory(loc, contents);
			}
		}

		m_emul.runProgram();
	}
}
