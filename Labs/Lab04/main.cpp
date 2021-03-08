#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

double ToDecimalMantissa(string radix)
{
	double decimalValue = 0.0;

	// extracts all bits after the binary point
	string binaryString = radix.substr(radix.find('.') + 1);

	// detects empty binaryString
	if (binaryString.length() == 0)
	{
		throw invalid_argument("invalid string");
	}

	// reads binaryString bit-by-bit
	for (int i = 0; i < binaryString.length(); i++)
	{
		// evaluates bit 1s
		if (binaryString[i] == '1')
		{
			decimalValue += pow(2, (-1 * (i + 1)));
		}
	}

	return decimalValue;
}

int main()
{
	string str;

	str = "0.101";
	cout << str << " base 2 = " << ToDecimalMantissa(str) << " base 10" << endl;

	str = ".00110101011101101";
	cout << str << " base 2 = " << ToDecimalMantissa(str) << " base 10" << endl;

	str = "0.0";
	cout << str << " base 2 = " << ToDecimalMantissa(str) << " base 10" << endl;

	str = "0";
	cout << str << " base 2 = " << ToDecimalMantissa(str) << " base 10" << endl;

	str = ".";
	cout << str << " base 2 = " << ToDecimalMantissa(str) << " base 10" << endl;

	return 0;
}