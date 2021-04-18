#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Log
{
private:
	ofstream file;

public:
	// constructor
	Log()
	{
		file.open("records.txt", ios_base::app);
	}

	// verifies and records binaryString to file
	void recordBinaryString(string id, string binaryString)
	{
		// rejects empty strings
		if (binaryString.empty())
		{
			return;
		}
		// rejects non-binary strings
		for (int i = 0; i < binaryString.size(); i++)
		{
			if (binaryString[i] != '0' && binaryString[i] != '1')
			{
				return;
			}
		}
		file << id << ' ' << binaryString << endl;
	}

	// converts binaryArray to binaryString and records it
	void recordBinaryArray(string id, vector<bool> &binaryArray)
	{
		string binaryString = "";
		// converts binaryArray element-by-element
		for (bool value : binaryArray)
		{
			if (value)
			{
				binaryString += '1';
			}
			else
			{
				binaryString += '0';
			}
		}
		recordBinaryString(id, binaryString);
	}

	// destructor
	~Log()
	{
		file.close();
	}
};

#endif