//
//	Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION

This function will place the symbol "a_symbol" and its location "a_loc"
in the symbol table.
*/
void
SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{

	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {
		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

/**/
/*

NAME

void SymbolTable::DisplaySymbolTable()

SYNOPSIS

void SymbolTable::DisplaySymbolTable() - prints the symbol table

DESCRIPTION

Prints the contents of the symbol table

RETURNS

Integer

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
void SymbolTable::DisplaySymbolTable()
{
	cout << "Symbol Table" << endl;
	cout << "Symbol #" << setw(15) << "Symbol" << setw(15) << "Location" << endl;
	int count = 0;
	for (map<string, int>::const_iterator it = m_symbolTable.begin();it != m_symbolTable.end(); ++it){
		cout << setw(3) << count << setw(18) << it->first << setw(15) << it->second << endl;
		count++;
	}
	cout << "-----------------------------------------------" << endl;
}

/**/
/*

NAME

bool SymbolTable::LookupSymbol(string & a_symbol, int & a_loc)

SYNOPSIS

bool SymbolTable::LookupSymbol(string & a_symbol, int & a_loc)
	a_symbol	-> the symbol to look up
	a_lov		-> the location of the symbol

DESCRIPTION

If the value in the symbol table isn't the location, return false.

RETURNS

True/False

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
bool SymbolTable::LookupSymbol(string & a_symbol, int & a_loc)
{
	if(m_symbolTable[a_symbol] != a_loc){
		return false;
	}
	return true;
}

/**/
/*

NAME

int SymbolTable::getLocation(string &a_symbol)

SYNOPSIS

int SymbolTable::getLocation(string &a_symbol)

DESCRIPTION

Returns the location for the specified symbol

RETURNS

Integer

AUTHOR

Caroline Silber

DATE

12/26/2016

*/
/**/
int SymbolTable::getLocation(string &a_symbol) {
	return m_symbolTable[a_symbol];
}