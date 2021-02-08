#include <iostream>
#include <vector>
using namespace std;

string ToBinaryString(vector<bool> &word)
{
	string str = "";

	// range-based for-loop
	for (auto val : word)
	{
		if (val)
		{
			str += '1';
		}
		else
		{
			str += '0';
		}
	}

	return str;
}

int main()
{
	vector<bool> word = {false, true, true, false, false, true};

	cout << ToBinaryString(word) << endl;

	return 0;
}