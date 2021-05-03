#include "Computer.h"
using namespace std;

// arithmetic program that evaluates (line 4095) = (line 4091) * (line 4092) / (line 4093) - (line 4094)
const string PROGRAM_FILENAME = "Program1.txt";

// array program that stores the sum of n adjacent memory locations in another memory location
// const string PROGRAM_FILENAME = "Program2.txt";

// comparison program that stores the result of determining if the content of a memory location represents a leap year
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