#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../PartB/Bus.h"
#include "../PartA/Log.h"
#include <iostream>
#include <cmath>
using namespace std;

const string PROCESSOR_SUCCESS = "00000000";
const string PROCESSOR_FAILURE = "00000001";

const string PROCESSOR_END = "00000000";
const string PROCESSOR_LOAD = "00010000";
const string PROCESSOR_SAVE = "00010001";
const string PROCESSOR_ADD = "00100000";
const string PROCESSOR_SUB = "00100001";
const string PROCESSOR_MUL = "00100010";
const string PROCESSOR_DIV = "00100011";
const string PROCESSOR_NOT = "00110000";
const string PROCESSOR_OR = "00110001";
const string PROCESSOR_AND = "00110010";
const string PROCESSOR_GO_TO_X = "01000000";
const string PROCESSOR_GO_TO = "01000001";

const vector<bool> END({false, false, false, false, false, false, false, false});
const vector<bool> LOAD({false, false, false, true, false, false, false, false});
const vector<bool> SAVE({false, false, false, true, false, false, false, true});
const vector<bool> ADD({false, false, true, false, false, false, false, false});
const vector<bool> SUB({false, false, true, false, false, false, false, true});
const vector<bool> MUL({false, false, true, false, false, false, true, false});
const vector<bool> DIV({false, false, true, false, false, false, true, true});
const vector<bool> NOT({false, false, true, true, false, false, false, false});
const vector<bool> OR({false, false, true, true, false, false, false, true});
const vector<bool> AND({false, false, true, true, false, false, true, false});
const vector<bool> GO_TO_X({false, true, false, false, false, false, false, false});
const vector<bool> GO_TO({false, true, false, false, false, false, false, true});

class Processor
{
private:
	Log *logger;

	Bus internalBus;
	Bus *externalBus;

	vector<bool> memoryBufferRegister;
	vector<bool> accumulator;

	vector<bool> memoryAddressRegister;
	vector<bool> programCounter;

	vector<bool> instructionRegister;

	// copy constructor
	Processor(const Processor &obj);

	// overloaded assignment operator
	Processor &operator=(const Processor &rhs);

	// returns binaryVector as decimal integer
	int toDecimalInt(vector<bool> binaryVector)
	{
		int decimalInt = 0;

		// reads binaryVector
		for (int i = 0; i < binaryVector.size(); i++)
		{
			if (binaryVector[i])
			{
				decimalInt += pow(2, binaryVector.size() - i - 1);
			}
		}

		return decimalInt;
	}

	// returns decimalInt as binary vector of size vectorSize
	vector<bool> toBinaryVector(int decimalInt, int vectorSize)
	{
		if (decimalInt < 0)
		{
			throw underflow_error("register underflow");
		}

		vector<bool> binaryVector;

		// appends bits to binaryVector's front until decimalInt becomes zero
		while (decimalInt)
		{
			binaryVector.insert(binaryVector.begin(), decimalInt % 2);
			decimalInt /= 2;
		}

		if (binaryVector.size() > vectorSize)
		{
			throw overflow_error("register overflow");
		}

		// pads binaryVector with zeroes until length equals vectorSize
		while (binaryVector.size() < vectorSize)
		{
			binaryVector.insert(binaryVector.begin(), false);
		}

		return binaryVector;
	}

	// adds one to programCounter
	void incrementProgramCounter()
	{
		programCounter = toBinaryVector(toDecimalInt(programCounter) + 1, ADDRESS_SIZE);
		logRegister(" PC", programCounter);
	}

	// records register to logger
	void logRegister(string registerID, vector<bool> registerVector)
	{
		if (logger != NULL)
		{
			logger->recordBinaryArray(registerID, registerVector);
		}
	}

	// fetches and decodes instructions, then delegate control to other methods for executions
	void Control()
	{
		// fetches data from externalBus
		for (int i = 0; i < DATA_SIZE; i++)
		{
			memoryBufferRegister[i] = externalBus->getDataBit(i);
		}
		logRegister("MBR", memoryBufferRegister);

		// fetches address from externalBus
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			memoryAddressRegister[i] = externalBus->getAddressBit(i);
		}
		logRegister("MAR", memoryAddressRegister);

		// fetches control from externalBus
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			internalBus.getControlBit(i) = externalBus->getControlBit(i);
			instructionRegister[i] = externalBus->getControlBit(i);
		}
		logRegister(" IR", instructionRegister);

		// decodes instruction
		if (instructionRegister == END)
		{
			return;
		}
		else if (instructionRegister == LOAD)
		{
			accumulator = memoryBufferRegister;
			logRegister(" AC", accumulator);
			incrementProgramCounter();
		}
		else if (instructionRegister == SAVE)
		{
			for (int i = 0; i < DATA_SIZE; i++)
			{
				externalBus->getDataBit(i) = accumulator[i];
			}
			incrementProgramCounter();
		}
		else if (instructionRegister == ADD || instructionRegister == SUB || instructionRegister == MUL || instructionRegister == DIV || instructionRegister == NOT || instructionRegister == OR || instructionRegister == AND)
		{
			ALU();
		}
		else if (instructionRegister == GO_TO_X)
		{
			programCounter = memoryAddressRegister;
			logRegister(" PC", programCounter);
		}
		else if (instructionRegister == GO_TO)
		{
			if (accumulator.back())
			{
				programCounter = memoryAddressRegister;
				logRegister(" PC", programCounter);
			}
			else
			{
				incrementProgramCounter();
			}
		}
		else
		{
			throw invalid_argument("invalid instruction");
		}
	}

	// performs all arithmetic/logic operations
	void ALU()
	{
		if (internalBus.getControlString() == PROCESSOR_ADD)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) + toDecimalInt(memoryBufferRegister), DATA_SIZE);
		}
		else if (internalBus.getControlString() == PROCESSOR_SUB)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) - toDecimalInt(memoryBufferRegister), DATA_SIZE);
		}
		else if (internalBus.getControlString() == PROCESSOR_MUL)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) * toDecimalInt(memoryBufferRegister), DATA_SIZE);
		}
		else if (internalBus.getControlString() == PROCESSOR_DIV)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) / toDecimalInt(memoryBufferRegister), DATA_SIZE);
		}
		else if (internalBus.getControlString() == PROCESSOR_NOT)
		{
			// performs logical NOT on AC
			for (int i = 0; i < DATA_SIZE; i++)
			{
				accumulator[i] = !accumulator[i];
			}
		}
		else if (internalBus.getControlString() == PROCESSOR_OR)
		{
			// performs logical OR on AC and M(X)
			for (int i = 0; i < DATA_SIZE; i++)
			{
				accumulator[i] = accumulator[i] || memoryBufferRegister[i];
			}
		}
		else if (internalBus.getControlString() == PROCESSOR_AND)
		{
			// performs logical AND on AC and M(X)
			for (int i = 0; i < DATA_SIZE; i++)
			{
				accumulator[i] = accumulator[i] && memoryBufferRegister[i];
			}
		}
		else
		{
			throw invalid_argument("invalid ALU operation");
		}

		logRegister(" AC", accumulator);
		incrementProgramCounter();
	}

	// assigns PROCESSOR_SUCCESS to internal control bus if Bus object is assigned, assigns PROCESSOR_FAILURE otherwise
	void Valid()
	{
		if (externalBus != NULL)
		{
			internalBus.setControlString(PROCESSOR_SUCCESS);
		}
		else
		{
			internalBus.setControlString(PROCESSOR_FAILURE);
		}
	}

public:
	// default constructor
	Processor()
	{
		externalBus = NULL;

		// assigns zeroes to memoryBufferRegister and accumulator
		for (int i = 0; i < DATA_SIZE; i++)
		{
			memoryBufferRegister.push_back(false);
			accumulator.push_back(false);
		}

		// assigns zeroes to memoryAddressRegister and programCounter
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			memoryAddressRegister.push_back(false);
			programCounter.push_back(false);
		}

		// assigns zeroes to instructionRegister
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			instructionRegister.push_back(false);
		}
	}

	// overloaded constructor
	Processor(Bus *bus, Log *log)
	{
		externalBus = bus;
		logger = log;

		// assigns zeroes to memoryBufferRegister and accumulator
		for (int i = 0; i < DATA_SIZE; i++)
		{
			memoryBufferRegister.push_back(false);
			accumulator.push_back(false);
		}

		// assigns zeroes to memoryAddressRegister and programCounter
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			memoryAddressRegister.push_back(false);
			programCounter.push_back(false);
		}

		// assigns zeroes to instructionRegister
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			instructionRegister.push_back(false);
		}
	}

	// sets externalBus pointer
	void setBus(Bus *bus)
	{
		externalBus = bus;
	}

	// sets logger pointer
	void setLogger(Log *log)
	{
		logger = log;
	}

	// calls Valid() then Control() if internal control bus contains PROCESSOR_SUCCESS
	void Process()
	{
		Valid();

		if (internalBus.getControlString() == PROCESSOR_SUCCESS)
		{
			Control();
		}
	}
};

#endif