#include <iostream>
#include <string>
using namespace std;

//define function below here
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
	if (infixString[0] < 'a' && infixString[0] > 'z')
	{
		return false;
	}
	// checks operand two
	if (infixString[4] < 'a' && infixString[4] > 'z')
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

string ToPrefix(string exp)
{
	if (verifyInfixString(exp))
	{
		return exp[2] + ' ' + exp[0] + ' ' + exp[4];
	}
	return "";
}
//define function above here

int main()
{
	cout << ToPrefix("a + b") << endl;
	
	return 0;
}
