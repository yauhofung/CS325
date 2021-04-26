#include "../PartA/Log.h"
#include "../PartB/Bus.h"
#include "../PartC/Memory.h"
#include "Processor.h"
using namespace std;

int main()
{
	Log log;
	Bus bus;
	Memory memory(&bus, MEMORY_FILENAME);
	Processor processor(&bus, &log);

	// adds line 1 by line 3 and stores result in AC
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

	return 0;
}