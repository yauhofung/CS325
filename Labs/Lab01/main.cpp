#include <iostream>
#include <fstream>
using namespace std;

bool BinaryStringWrite(string word, ofstream &out)
{
	if (word.empty())
	{
		return false;
	}

	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] != '0' && word[i] != '1')
		{
			return false;
		}
	}

	out << word << '\n';
	return true;
}

void displaysInfo(string word, ofstream &out)
{
	if (BinaryStringWrite(word, out))
	{
		cout << word << " is a binary string.\n";
	}
	else
	{
		cout << word << " is not a binary string.\n";
	}
}

int main()
{
	string word;
	ofstream file("binary.txt");

	word = "1111";
	displaysInfo(word, file);

	word = "10101";
	displaysInfo(word, file);

	word = "1 0 1 0 1";
	displaysInfo(word, file);

	word = "";
	displaysInfo(word, file);

	file.close();

	return 0;
}