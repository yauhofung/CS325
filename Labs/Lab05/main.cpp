#include <iostream>
using namespace std;

void MemoryIO(bool bus[], string memory[])
{
	int address = 0;
	if (bus[1])
	{
		address += 4;
	}
	if (bus[4])
	{
		address += 2;
	}
	if (bus[7])
	{
		address += 1;
	}

	if (bus[0] && !bus[3] && bus[6])
	{
		string dataString = "000";
		if (bus[2])
		{
			dataString[0] = '1';
		}
		if (bus[5])
		{
			dataString[1] = '1';
		}
		if (bus[8])
		{
			dataString[2] = '1';
		}

		memory[address] = dataString;
		bus[0] = bus[3] = bus[6] = false;
	}
	else if (!bus[0] && bus[3] && bus[6])
	{
		if (memory[address][0] == '0')
		{
			bus[2] = false;
		}
		else
		{
			bus[2] = true;
		}

		if (memory[address][1] == '0')
		{
			bus[5] = false;
		}
		else
		{
			bus[5] = true;
		}

		if (memory[address][2] == '0')
		{
			bus[8] = false;
		}
		else
		{
			bus[8] = true;
		}

		bus[0] = bus[3] = bus[6] = false;
	}
}

int main()
{
	bool bus[] = {true, false, true, false, true, true, true, true, false};
	string memory[] = {"000", "001", "010", "011", "100", "101", "110", "111"};

	cout << "Before:\n";
	for (int b = 0; b < 9; b++)
	{
		cout << bus[b] << ' ';
	}
	cout << endl;
	for (int m = 0; m < 8; m++)
	{
		cout << memory[m] << ' ';
	}
	cout << endl;

	MemoryIO(bus, memory);

	cout << "After:\n";
	for (int b = 0; b < 9; b++)
	{
		cout << bus[b] << ' ';
	}
	cout << endl;
	for (int m = 0; m < 8; m++)
	{
		cout << memory[m] << ' ';
	}
	cout << endl;

	return 0;
}