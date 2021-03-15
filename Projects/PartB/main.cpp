#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bus.h"
using namespace std;

int main()
{
	srand(time(NULL));

	Bus obj;

	// stores random data in obj
	for (int i = 0; i < DATA_SIZE; i++)
	{
		obj.getDataBit(i) = rand() % 2;
	}
	// stores random address in obj
	for (int i = 0; i < ADDRESS_SIZE; i++)
	{
		obj.getAddressBit(i) = rand() % 2;
	}
	// stores random control in obj
	for (int i = 0; i < CONTROL_SIZE; i++)
	{
		obj.getControlBit(i) = rand() % 2;
	}

	cout << obj;

	return 0;
}
