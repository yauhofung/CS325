#include <iostream>
#include "Helper.h"
using namespace std;

const string HEXFILENAME = "hex.txt";

int main()
{
	if (ProgramConverter(HEXFILENAME))
	{
		cout << "Created " << BINARYFILENAME << " from " << HEXFILENAME << ".\n";
	}
	else
	{
		cout << "Detected invalid hexadecimal string in " << HEXFILENAME << ".\n";
	}

	return 0;
}