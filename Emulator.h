//
//		Emulator class - supports the emulation of VC3600 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class emulator {

public:

	const static int MEMSZ = 10000;	// The size of the memory of the VC3600.
	emulator() {
		memset(m_memory, 0, MEMSZ * sizeof(int));
	}
	// Records instructions and data into VC3600 memory.
	bool insertMemory(int a_location, int a_contents);

	// Runs the VC3600 program recorded in memory.
	void runProgram();

private:
	// Various instructions
	void Add();
	void Sub();
	void Mult();
	void Div();
	void Load();
	void Store();
	void Read();
	void Write();
	void Branch();
	void Bm();
	void Bz();
	void Bp();
	void Halt();

	// initial memory location
	int m_origin;
	bool m_isFirst = true;
	int m_loc;
	bool m_terminate = false;

	pair <int, int> m_instruction;

	int m_memory[MEMSZ];       // The memory of the VC3600.
	int accumulator;			// The accumulator for the VC3600
};

#endif
