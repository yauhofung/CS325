#include "../PartA/Log.h"
#include "../PartB/Bus.h"
#include "../PartC/Memory.h"
#include "Processor.h"
using namespace std;

int main()
{
	Log log;
	Bus bus;
	Memory memory(log, bus, MEMORY_FILENAME);
	Processor processor(bus, log);

	// adds line 1 by line 3 and stores result in line 8
	bus.setAddressString("000000000000");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_LOAD);
	processor.Process();

	bus.setAddressString("000000000010");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_ADD);
	processor.Process();

	bus.setControlString(PROCESSOR_SAVE);
	processor.Process();

	bus.setControlString(MEMORY_WRITE);
	bus.setAddressString("000000000111");
	memory.Process();

	// divides line 4 by line 2 and stores result in line 9
	bus.setAddressString("000000000011");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_LOAD);
	processor.Process();

	bus.setAddressString("000000000001");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_DIV);
	processor.Process();

	bus.setControlString(PROCESSOR_SAVE);
	processor.Process();

	bus.setControlString(MEMORY_WRITE);
	bus.setAddressString("000000001000");
	memory.Process();

	// performs logical NOT on line 5 and stores result in line 10
	bus.setAddressString("000000000100");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_LOAD);
	processor.Process();

	bus.setControlString(PROCESSOR_NOT);
	processor.Process();

	bus.setControlString(PROCESSOR_SAVE);
	processor.Process();

	bus.setControlString(MEMORY_WRITE);
	bus.setAddressString("000000001001");
	memory.Process();

	// performs logical AND on line 6 with line 7 and stores result in line 11
	bus.setAddressString("000000000101");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_LOAD);
	processor.Process();

	bus.setAddressString("000000000110");
	bus.setControlString(MEMORY_READ);
	memory.Process();

	bus.setControlString(PROCESSOR_AND);
	processor.Process();

	bus.setControlString(PROCESSOR_SAVE);
	processor.Process();

	bus.setControlString(MEMORY_WRITE);
	bus.setAddressString("000000001010");
	memory.Process();

	return 0;
}