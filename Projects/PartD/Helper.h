#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <fstream>
using namespace std;

const string BINARYFILENAME = "binary.txt";

// creates a binary copy of hexFilename and returns true if hexFilename contains valid hexadecimal strings, returns false otherwise
bool ProgramConverter(string hexFilename)
{
	ifstream hexFile(hexFilename);

	string hexString = "";
	string binaryString = "";

	// reads hexFile line-by-line
	while (getline(hexFile, hexString))
	{
		if (hexString.length() != 4)
		{
			return false;
		}
		// converts hexadecimal value character-by-character
		for (int i = 0; i < hexString.length(); i++)
		{
			if (hexString[i] == '0')
			{
				binaryString += "0000";
			}
			else if (hexString[i] == '1')
			{
				binaryString += "0001";
			}
			else if (hexString[i] == '2')
			{
				binaryString += "0010";
			}
			else if (hexString[i] == '3')
			{
				binaryString += "0011";
			}
			else if (hexString[i] == '4')
			{
				binaryString += "0100";
			}
			else if (hexString[i] == '5')
			{
				binaryString += "0101";
			}
			else if (hexString[i] == '6')
			{
				binaryString += "0110";
			}
			else if (hexString[i] == '7')
			{
				binaryString += "0111";
			}
			else if (hexString[i] == '8')
			{
				binaryString += "1000";
			}
			else if (hexString[i] == '9')
			{
				binaryString += "1001";
			}
			else if (hexString[i] == 'A')
			{
				binaryString += "1010";
			}
			else if (hexString[i] == 'B')
			{
				binaryString += "1011";
			}
			else if (hexString[i] == 'C')
			{
				binaryString += "1100";
			}
			else if (hexString[i] == 'D')
			{
				binaryString += "1101";
			}
			else if (hexString[i] == 'E')
			{
				binaryString += "1110";
			}
			else if (hexString[i] == 'F')
			{
				binaryString += "1111";
			}
			else
			{
				return false;
			}
		}
		binaryString += '\n';
	}
	hexFile.close();

	ofstream binaryFile(BINARYFILENAME);
	binaryFile << binaryString;
	binaryFile.close();

	return true;
}

#endif