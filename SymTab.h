//
//		Symbol table class.
//
#pragma once



// This class is our symbol table.
class SymbolTable {

public:
	// Get rid of constructor and destructor if you don't need them.
	SymbolTable() {};
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	bool LookupSymbol(string &a_symbol, int &a_loc);

	// get a location form the symbol table
	int SymbolTable::getLocation(string &a_symbol);

	// Check if a symbol is multiply defined
	inline bool isMultiplyDefined(string &a_symbol) {
		if (m_symbolTable[a_symbol] == multiplyDefinedSymbol) {
			return true;
		}
		return false;
	}

private:

	// This is the actual symbol table.  The symbol is the key to the map.
	map<string, int> m_symbolTable;

};