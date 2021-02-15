#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Log
{
private:
	int id;
	ofstream file;

public:
	// constructor
	Log()
	{
		id = 0;
		file.open("records.txt");
	}

	// verifies and records binaryString to file
	void recordBinaryString(string binaryString)
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
		id++;
		cout << "Recorded " << binaryString << ".\n";
	}

	// converts binaryArray to binaryString and records it
	void recordBinaryArray(vector<bool> &binaryArray)
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
		recordBinaryString(binaryString);
	}

	// destructor
	~Log()
	{
		file.close();
	}
};

#endif