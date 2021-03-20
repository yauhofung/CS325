#include <iostream>
#include "Helper.h"
using namespace std;

int main()
{
	const string hexFilename = "hex.txt";

	if (ProgramConverter(hexFilename))
	{
		cout << "File converted.\n";
	}
	else
	{
		cout << "Invalid hexadecimal string detected.\n";
	}

	return 0;
}