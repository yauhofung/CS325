#ifndef MEMORY_H
#define MEMORY_H

#include "../PartB/Bus.h"
#include <iostream>
#include <fstream>
using namespace std;

// control signals
const string FAIL = "00000000";
const string SUCCESS = "00000001";
const string WRITE = "00000010";
const string READ = "00000011";

class Memory
{
private:
	Bus *busPtr;
	string filename;

	// copy constructor
	Memory(const Memory &obj);

	// overloaded assignment operator
	Memory &operator=(const Memory &rhs);

	// writes data to file at address
	void Write()
	{
		fstream file(filename);

		// sets output position at specified address
		file.seekp(busPtr->getAddressInt() * (DATA_SIZE + 2));

		file << busPtr->getDataString();

		file.close();
	}

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

public:
	// default constructor
	Memory()
	{
		busPtr = NULL;
		filename = "";
	}
	// overloaded constructor
	Memory(Bus *bus, string file)
	{
		busPtr = bus;
		filename = file;
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

	// returns true if a Bus is assigned and the file is valid
	bool Valid()
	{
		if (busPtr == NULL)
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

	// calls Write() or Read() based on the control signal
	void Process()
	{
		if (Valid() && busPtr->getControlString() == WRITE)
		{
			Write();
			busPtr->setControlString(SUCCESS);
		}
		else if (Valid() && busPtr->getControlString() == READ)
		{
			Read();
			busPtr->setControlString(SUCCESS);
		}
		else
		{
			busPtr->setControlString(FAIL);
		}
	}

	// destructor
	~Memory() {}
};

#endif