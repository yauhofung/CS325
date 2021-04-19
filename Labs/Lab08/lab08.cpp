#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

std::string ToString(bool a[])
{
	std::string r = "";

	for(int i = 0;i < 32;i += 1)
	{
		r += (a[i])?("1"):("0");
	}
	return r;
}

void PopulateWord(bool a[])
{
	for(int i = 0;i < 32;i += 1)
	{
		a[i] = (rand() % 2 == 0);
	}
}

int main()
{
	srand(time(NULL));
	bool a[32], b[32], r[32];
	PopulateWord(a);
	PopulateWord(b);
	
	std::cout << "a = " << ToString(a) << "\n";
	std::cout << "b = " << ToString(b) << "\n";

	return 0;
}
