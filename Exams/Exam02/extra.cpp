#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct Process
{
	char name;
	int runtime;
};

void BuildProcess(Process& process)
{
	static char n = 'A';

	process.name = n;
	process.runtime = rand() % 100 + 1;

	if(n == 'Z')
	{
		n = 'A';
	}
	else 
	{
		n += 1;
	}
}

//n is the size of the array
bool BuildProcessArray(Process processes[],int n)
{
	if(n > 0 && n < 26)
	{
		for(int i = 0;i < n;i += 1)
		{
			BuildProcess(processes[i]);
		}
	}
}

/****************************
Define Function Below Here
****************************/


/***************************
Define Function Above Here
***************************/ 

int main()
{
	srand(time(NULL));
	return 0;
}
