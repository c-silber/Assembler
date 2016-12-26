//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include "Errors.h"

class Assembler {

public:
	Assembler(int argc, char *argv[]);
	~Assembler();

	// Pass1 - establish the locations of the symbols
	void PassI();

	// Pass II - generate a translation
	void PassII();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

	void PrintTranslation();

	// Run emulator on the translation.
	void RunEmulator();

	// struct to hold the translation
	struct trans {
		int location;
		string contents;
		string org;
	};


private:

	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab;	// Symbol table object
	Instruction m_inst;	    // Instruction object
	emulator m_emul;        // Emulator object
	Errors m_err;			// Error object

	// vector to hold the translation
	vector <trans> translationVect;
};
