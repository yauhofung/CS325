#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../PartB/Bus.h"
#include "../PartA/Log.h"
#include <cmath>
using namespace std;

const string SUCCESS = "00000000";
const string FAILURE = "00000001";

const string END_STRING = "00000000";
const string LOAD_STRING = "00010000";
const string SAVE_STRING = "00010001";
const string ADD_STRING = "00100000";
const string SUB_STRING = "00100001";
const string MUL_STRING = "00100010";
const string DIV_STRING = "00100011";
const string GO_TO_X_STRING = "00110000";
const string GO_TO_STRING = "01000000";

const vector<bool> END({false, false, false, false, false, false, false, false});
const vector<bool> LOAD({false, false, false, true, false, false, false, false});
const vector<bool> SAVE({false, false, false, true, false, false, false, true});
const vector<bool> ADD({false, false, true, false, false, false, false, false});
const vector<bool> SUB({false, false, true, false, false, false, false, true});
const vector<bool> MUL({false, false, true, false, false, false, true, false});
const vector<bool> DIV({false, false, true, false, false, false, true, true});
const vector<bool> GO_TO_X({false, false, true, true, false, false, false, false});
const vector<bool> GO_TO({false, true, false, false, false, false, false, false});

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
		int decimalInt;
		// converts binaryVector to decimal integer bit-by-bit
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
		vector<bool> binaryVector;
		// appends bit-by-bit to front of binaryVector until decimalInt becomes zero
		while (decimalInt)
		{
			binaryVector.insert(binaryVector.begin(), decimalInt % 2);
			decimalInt /= 2;
		}
		if (binaryVector.size() > vectorSize)
		{
			throw overflow_error("register overflow");
		}
		// pads binaryVector with zeroes until its length equals vectorSize
		while (binaryVector.size() < vectorSize)
		{
			binaryVector.insert(binaryVector.begin(), false);
		}
		return binaryVector;
	}

	// increases programCounter by one
	void incrementProgramCounter()
	{
		programCounter = toBinaryVector(toDecimalInt(programCounter) + 1, ADDRESS_SIZE);
		logRegister("programCounter", programCounter);
	}

	// logs register after modification
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
		instructionRegister.clear();
		// fetches instruction from externalBus
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			instructionRegister.push_back(externalBus->getControlBit(i));
			internalBus.getControlBit(i) = externalBus->getControlBit(i);
		}
		// decodes instruction
		if (instructionRegister == END)
		{
			return;
		}
		else if (instructionRegister == LOAD)
		{
			for (int i = 0; i < DATA_SIZE; i++)
			{
				accumulator.push_back(externalBus->getDataBit(i));
			}
			logRegister("accumulator", accumulator);
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
		else if (instructionRegister == ADD || instructionRegister == SUB || instructionRegister == MUL || instructionRegister == DIV)
		{
			ALU();
		}
		else if (instructionRegister == GO_TO_X)
		{
			programCounter = memoryAddressRegister;
			logRegister("programCounter", programCounter);
		}
		else if (instructionRegister == GO_TO)
		{
			// branches based on accumulator parity
			if (accumulator.back())
			{
				programCounter = memoryAddressRegister;
				logRegister("programCounter", programCounter);
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
		int operand = toDecimalInt(memoryBufferRegister);
		// preforms arithmetic operation based on internal control bus
		if (internalBus.getControlString() == ADD_STRING)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) + operand, DATA_SIZE);
		}
		else if (internalBus.getControlString() == SUB_STRING)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) - operand, DATA_SIZE);
		}
		else if (internalBus.getControlString() == MUL_STRING)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) * operand, DATA_SIZE);
		}
		else if (internalBus.getControlString() == DIV_STRING)
		{
			accumulator = toBinaryVector(toDecimalInt(accumulator) / operand, DATA_SIZE);
		}
		else
		{
			throw invalid_argument("invalid arithmetic operation");
		}
		logRegister("accumulator", accumulator);
		incrementProgramCounter();
	}

	// assigns SUCCESS to internal control bus if Bus object is assigned, assigns FAILURE otherwise
	void Valid()
	{
		if (externalBus != NULL)
		{
			internalBus.setControlString(SUCCESS);
		}
		else
		{
			internalBus.setControlString(FAILURE);
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

	// calls Valid() then Control() if internal control bus contains SUCCESS
	void Process()
	{
		Valid();
		if (internalBus.getControlString() == SUCCESS)
		{
			Control();
		}
	}
};

#endif