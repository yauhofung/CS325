#ifndef MEMORY_H
#define MEMORY_H

#include "../PartA/Log.h"
#include "../PartB/Bus.h"
#include <iostream>
#include <fstream>
using namespace std;

const string MEMORY_FILENAME = "memory.txt";

// control signals
const string MEMORY_SUCCESS = "00000000";
const string MEMORY_FAILURE = "00000001";
const string MEMORY_READ = "00010000";
const string MEMORY_WRITE = "00010001";

class Memory
{
private:
	Log *logPtr;
	Bus *busPtr;
	string filename;

	// copy constructor
	Memory(const Memory &obj);

	// overloaded assignment operator
	Memory &operator=(const Memory &rhs);

	// reads data to bus at address
	void Read()
	{
		ifstream file(filename);

		// sets input position at specified address
		file.seekg(busPtr->getAddressInt() * (DATA_SIZE + 2));

		string dataString;
		file >> dataString;
		busPtr->setDataString(dataString);

		file.close();
	}

	// writes data to file at address
	void Write()
	{
		fstream file(filename);

		// sets output position at specified address
		file.seekp(busPtr->getAddressInt() * (DATA_SIZE + 2));

		file << busPtr->getDataString();

		file.close();
	}

public:
	// default constructor
	Memory()
	{
		logPtr = NULL;
		busPtr = NULL;
		filename = "";
	}
	// overloaded constructor
	Memory(Log &log, Bus &bus, string file)
	{
		logPtr = &log;
		busPtr = &bus;
		filename = file;
	}

	// sets logPtr to log
	void setLog(Log &log)
	{
		logPtr = &log;
	}
	// sets busPtr to bus
	void setBus(Bus &bus)
	{
		busPtr = &bus;
	}
	// sets filename to file
	void setFile(string file)
	{
		filename = file;
	}

	// returns true if a Log is assigned, a Bus is assigned, and the file is valid
	bool Valid()
	{
		if (logPtr == NULL || busPtr == NULL)
		{
			return false;
		}
		ifstream file(filename);
		if (!file.is_open())
		{
			return false;
		}
		if (file.peek() == EOF)
		{
			return false;
		}
		string line;
		// checks file line-by-line
		while (getline(file, line))
		{
			if (line.length() != DATA_SIZE)
			{
				file.close();
				return false;
			}
			// checks line bit-by-bit
			for (int i = 0; i < DATA_SIZE; i++)
			{
				if (line[i] != '0' && line[i] != '1')
				{
					file.close();
					return false;
				}
			}
		}
		file.close();
		return true;
	}

	// calls Read() or Write() based on the control signal
	void Process()
	{
		if (Valid() && busPtr->getControlString() == MEMORY_READ)
		{
			Read();
			busPtr->setControlString(MEMORY_SUCCESS);
		}
		else if (Valid() && busPtr->getControlString() == MEMORY_WRITE)
		{
			Write();
			busPtr->setControlString(MEMORY_SUCCESS);
		}
		else
		{
			busPtr->setControlString(MEMORY_FAILURE);
		}
	}

	// destructor
	~Memory() {}
};

#endif