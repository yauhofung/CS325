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

	bus.setControlString(END_STRING);
	processor.Process();
	bus.setControlString(LOAD_STRING);
	processor.Process();
	bus.setControlString(SAVE_STRING);
	processor.Process();
	bus.setControlString(ADD_STRING);
	processor.Process();
	bus.setControlString(SUB_STRING);
	processor.Process();
	bus.setControlString(MUL_STRING);
	processor.Process();
	bus.setControlString(DIV_STRING);
	processor.Process();
	bus.setControlString(GO_TO_X_STRING);
	processor.Process();
	bus.setControlString(GO_TO_STRING);
	processor.Process();

	return 0;
}