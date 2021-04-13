#include <iostream>
#include <string>
using namespace std;

//define function below here
// returns false if infixString is invalid, true otherwise
bool verifyInfixString(string infixString)
{
	// checks length
	if (infixString.length() != 5)
	{
		return false;
	}
	// checks operator
	if (infixString[2] != '+' && infixString[2] != '-' && infixString[2] != '*' && infixString[2] != '/' && infixString[2] != '%')
	{
		return false;
	}
	// checks operand one
	if (infixString[0] < 'a' || infixString[0] > 'z')
	{
		return false;
	}
	// checks operand two
	if (infixString[4] < 'a' || infixString[4] > 'z')
	{
		return false;
	}
	// checks the two whitespaces
	if (infixString[1] != ' ' || infixString[3] != ' ')
	{
		return false;
	}
	return true;
}

// returns exp in prefix notation
string ToPrefix(string exp)
{
	string prefixString = "";
	if (verifyInfixString(exp))
	{
		// prefix operator
		prefixString += exp[2];
		prefixString += ' ';
		// operand one
		prefixString += exp[0];
		prefixString += ' ';
		// operand two
		prefixString += exp[4];
	}
	return prefixString;
}
//define function above here

int main()
{
	cout << ToPrefix("a + z") << endl;
	cout << ToPrefix("b - y") << endl;
	cout << ToPrefix("c * x") << endl;
	cout << ToPrefix("d / w") << endl;
	cout << ToPrefix("e % v") << endl;

	cout << "Invalid string 1: " << ToPrefix("123456") << endl;
	cout << "Invalid string 2: " << ToPrefix("a b c") << endl;
	cout << "Invalid string 3: " << ToPrefix("A + z") << endl;
	cout << "Invalid string 4: " << ToPrefix("a + Z") << endl;
	cout << "Invalid string 5: " << ToPrefix("a_+ Z") << endl;
	cout << "Invalid string 6: " << ToPrefix("a +_Z") << endl;

	return 0;
}
