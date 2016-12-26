//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

	Instruction() { };
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage,		// A machine language instruction
		ST_AssemblerInstr,		// Assembler Language instruction
		ST_Comment,				// Comment or blank line
		ST_End                  // end instruction
	};

	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);
	
	// To determine if it's an opCode
	bool isOpCode(string a_value);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	bool IsValidLabel();

	inline string &GetOperand() {
		if (isOperand()) {
			return m_Operand;
		}
		else {
			m_Operand = "000";
			return m_Operand;
		}
	}
	// To determine if an operand is blank
	inline bool isOperand() {

		return !m_Operand.empty();
	};

	// To access the label
	inline string &GetLabel() {
		return m_Label;
	};
	// To determine if a label is blank.
	inline bool isLabel() {

		return !m_Label.empty();
	};

	inline string getOpCode() {
		if (m_NumOpCode == 0) {
			return to_string(m_NumOpCode);
		}
		if (m_NumOpCode < 10) {
			return "0" + to_string(m_NumOpCode) + "0";
		}
		return to_string(m_NumOpCode) + "0";
	}

	inline int getConstant() {
		return m_Constant;
	}


private:

	// The elemements of a instruction
	string m_Label;         // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.

	string m_instruction;    // The original instruction.

							 // Derived values.
	int m_Constant = 0;
	int m_NumOpCode = 0;		// The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.

	int m_origin;
	int m_next;
};

