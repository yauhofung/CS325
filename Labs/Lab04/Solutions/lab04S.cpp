#include <iostream>
#include <string>

/******************************************************************************
Q: How many digits will be in the conversion of the base 8 number 6123167235
to binary
A: 3 * 10 = 30 digits

Q: What is a nibble?
A: A group of 4 bits (half a byte)

Q: State the digits of a base 12 number system and convert the decimal number
132 to base 12.
A: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B; B0

Q: Convert the hexadecimal number BAD.F to decimal.
A: 11 x 16^2 + 10 x 16 + 13 x 1 + 15 x 16^(-1) = 2989.9375
******************************************************************************/

double ToDecimalMantissa(std::string radix)
{
	double result = 0;
	int n = radix.size(), i = 0;

	while(i < n && radix[i] != '.')
	{
		if(radix[i] != '0')
		{
			return result;
		}
		i += 1;
	}
	
	i += 1;
	int cnt = 0; //numerical types are limited
	double two = 2;

	while(cnt < 31 && i < n)
	{
		result += (radix[i] - '0') / two;
		two *= 2;
		cnt += 1;
		i += 1;
	}

	return result;
}

int main()
{
	std::cout << ToDecimalMantissa("0.101") << "\n";
	return 0;
}
			
