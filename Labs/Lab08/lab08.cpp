#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void GE(bool a[], bool b[], bool r[])
{
	bool isGreaterOrEqual = false;
	bool compareBits = true;
	int index = 0;

	// compares a[] and b[] bit-by-bit
	while (compareBits && index < 32)
	{
		// greater bit
		if (a[index] > b[index])
		{
			isGreaterOrEqual = true;
			compareBits = false;
		}
		// lesser bit
		else if (a[index] < b[index])
		{
			compareBits = false;
		}
		// equal bit
		else
		{
			index++;
		}
	}

	// a[] and b[] are equivalent
	if (index == 32)
	{
		isGreaterOrEqual = true;
	}

	// evaluates result
	if (isGreaterOrEqual)
	{
		fill(r, r + 32, false);
	}
	else
	{
		fill(r, r + 32, true);
	}
}

std::string ToString(bool a[])
{
	std::string r = "";

	for (int i = 0; i < 32; i += 1)
	{
		r += (a[i]) ? ("1") : ("0");
	}
	return r;
}

void PopulateWord(bool a[])
{
	for (int i = 0; i < 32; i += 1)
	{
		a[i] = (rand() % 2 == 0);
	}
}

int main()
{
	srand(time(NULL));
	bool a[32], b[32], r[32];

	// random
	PopulateWord(a);
	PopulateWord(b);
	GE(a, b, r);
	std::cout << "\n";
	std::cout << "a = " << ToString(a) << "\n";
	std::cout << "b = " << ToString(b) << "\n";
	std::cout << "r = " << ToString(r) << "\n";

	// greater
	fill(a, a + 32, true);
	fill(b, b + 32, false);
	GE(a, b, r);
	std::cout << "\n";
	std::cout << "a = " << ToString(a) << "\n";
	std::cout << "b = " << ToString(b) << "\n";
	std::cout << "r = " << ToString(r) << "\n";

	// lesser
	fill(a, a + 32, false);
	fill(b, b + 32, true);
	GE(a, b, r);
	std::cout << "\n";
	std::cout << "a = " << ToString(a) << "\n";
	std::cout << "b = " << ToString(b) << "\n";
	std::cout << "r = " << ToString(r) << "\n";

	// equal
	fill(a, a + 32, false);
	fill(b, b + 32, false);
	GE(a, b, r);
	std::cout << "\n";
	std::cout << "a = " << ToString(a) << "\n";
	std::cout << "b = " << ToString(b) << "\n";
	std::cout << "r = " << ToString(r) << "\n";

	return 0;
}
