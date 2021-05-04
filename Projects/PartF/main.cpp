#include "Computer.h"
using namespace std;

// arithmetic program that stores the result of (line 4091) * (line 4092) / (line 4093) - (line 4094) in line 4095
// const string PROGRAM_FILENAME = "Program1.txt";

// array program that stores the sum of (line 4093) adjacent memory locations in line 4095 where the first element's location is specified on line 4094
const string PROGRAM_FILENAME = "Program2.txt";

// comparison program that stores (line 4093) to line 4095 if (line 4091) represents a leap year, stores (line 4094) otherwise
// const string PROGRAM_FILENAME = "Program3.txt";

int main()
{
	Log log;

	Processor processor;
	processor.setLogger(log);

	Memory memory;
	memory.setLog(log);
	memory.setFile(PROGRAM_FILENAME);

	Computer computer(memory, processor, log);
	computer.Power();

	return 0;
}