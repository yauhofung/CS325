#include <iostream>
using namespace std;

// converts hexadecimal word into binary string
string ToBinaryString(string word)
{
	string binaryString = "";
	// reads and converts word to binary character-by-character
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == '0')
		{
			binaryString += "0000";
		}
		else if (word[i] == '1')
		{
			binaryString += "0001";
		}
		else if (word[i] == '2')
		{
			binaryString += "0010";
		}
		else if (word[i] == '3')
		{
			binaryString += "0011";
		}
		else if (word[i] == '4')
		{
			binaryString += "0100";
		}
		else if (word[i] == '5')
		{
			binaryString += "0101";
		}
		else if (word[i] == '6')
		{
			binaryString += "0110";
		}
		else if (word[i] == '7')
		{
			binaryString += "0111";
		}
		else if (word[i] == '8')
		{
			binaryString += "1000";
		}
		else if (word[i] == '9')
		{
			binaryString += "1001";
		}
		else if (word[i] == 'A')
		{
			binaryString += "1010";
		}
		else if (word[i] == 'B')
		{
			binaryString += "1011";
		}
		else if (word[i] == 'C')
		{
			binaryString += "1100";
		}
		else if (word[i] == 'D')
		{
			binaryString += "1101";
		}
		else if (word[i] == 'E')
		{
			binaryString += "1110";
		}
		else if (word[i] == 'F')
		{
			binaryString += "1111";
		}
		else
		{
			binaryString += "XXXX";
		}
	}
	return binaryString;
}

int main()
{
	string word;

	word = "";
	cout << word << " base 16 = " << ToBinaryString(word) << " base 2\n";

	word = "A4";
	cout << word << " base 16 = " << ToBinaryString(word) << " base 2\n";

	word = "0123456789ABCDEF";
	cout << word << " base 16 = " << ToBinaryString(word) << " base 2\n";

	word = "HELLO";
	cout << word << " base 16 = " << ToBinaryString(word) << " base 2\n";

	return 0;
}