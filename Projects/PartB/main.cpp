#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Bus.h"
using namespace std;

int main()
{
	Bus obj;

	srand(time(NULL));
	// stores random values in obj
	for (int i = 0; i < SIZE; i++)
	{
		obj.getData(i) = rand() % 2;
		obj.getAddress(i) = rand() % 2;
		obj.getControl(i) = rand() % 2;
	}

	cout << obj;

	return 0;
}