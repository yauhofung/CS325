#include "Memory.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// generates memory file with random data
void generateFile()
{
	srand(time(NULL));

	ofstream file(MEMORY_FILENAME);
	// generates file line-by-line
	for (int i = 0; i < pow(2, ADDRESS_SIZE); i++)
	{
		// generates line bit-by-bit
		for (int j = 0; j < DATA_SIZE; j++)
		{
			file << rand() % 2;
		}
		file << '\n';
	}
	file.close();
}

int main()
{
	generateFile();

	Log log;
	Bus bus;
	Memory memory(log, bus, MEMORY_FILENAME);

	// reads from line 1
	bus.setAddressString("000000000000");
	bus.setControlString(MEMORY_READ);
	memory.Process();
	cout << bus << endl;

	// reads from line 4095
	bus.setAddressString("111111111110");
	bus.setControlString(MEMORY_READ);
	memory.Process();
	cout << bus << endl;

	// writes to line 2
	bus.setDataString("11111111111111111111111111111111");
	bus.setAddressString("000000000001");
	bus.setControlString(MEMORY_WRITE);
	memory.Process();
	cout << bus << endl;

	// writes to line 4096
	bus.setDataString("11111111000000001111111100000000");
	bus.setAddressString("111111111111");
	bus.setControlString(MEMORY_WRITE);
	memory.Process();
	cout << bus << endl;

	return 0;
}