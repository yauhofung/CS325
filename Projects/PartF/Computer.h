#ifndef COMPUTER_H
#define COMPUTER_H

#include "../PartA/Log.h"
#include "../PartB/Bus.h"
#include "../PartC/Memory.h"
#include "../PartE/Processor.h"
using namespace std;

class Computer
{
private:
	Bus systemBus;
	Memory *memoryPtr;
	Processor *processorPtr;
	Log *logPtr;

	// copy constructor
	Computer(const Computer &obj);

	// overloaded assignment operator
	Computer &operator=(const Computer &rhs);

public:
	// default contructor
	Computer()
	{
		memoryPtr = NULL;
		processorPtr = NULL;
		logPtr = NULL;
	}

	// overloaded constructor
	Computer(Memory &memory, Processor &processor, Log &log)
	{
		memoryPtr = &memory;
		processorPtr = &processor;
		logPtr = &log;
	}

	// sets memoryPtr
	void setMemory(Memory &memory)
	{
		memoryPtr = &memory;
	}

	// sets processorPtr
	void setProcessor(Processor &processor)
	{
		processorPtr = &processor;
	}

	// sets logPtr
	void setLog(Log &log)
	{
		logPtr = &log;
	}

	// executes code in memory starting from line 0 if all pointer fields aren't NULL
	void Power()
	{
		if (memoryPtr != NULL && processorPtr != NULL && logPtr != NULL)
		{
			memoryPtr->setBus(systemBus);
			processorPtr->setBus(systemBus);

			while (true)
			{
				systemBus.setAddressString(processorPtr->getProgramCounter());
				systemBus.setControlString(MEMORY_READ);
				memoryPtr->Process();

				string opcode = "";
				// stores control from data bus to opcode
				for (int i = 0; i < CONTROL_SIZE; i++)
				{
					opcode += to_string(systemBus.getDataBit(i));
				}
				if (opcode == PROCESSOR_END)
				{
					break;
				}

				// stores address from data bus to system address bus
				for (int i = CONTROL_SIZE; i < CONTROL_SIZE + ADDRESS_SIZE; i++)
				{
					systemBus.getAddressBit(i - CONTROL_SIZE) = systemBus.getDataBit(i);
				}
				systemBus.setControlString(MEMORY_READ);
				memoryPtr->Process();

				systemBus.setControlString(opcode);
				processorPtr->Process();

				if (opcode == PROCESSOR_SAVE)
				{
					systemBus.setControlString(MEMORY_WRITE);
					memoryPtr->Process();
				}
			}
		}
	}
};

#endif