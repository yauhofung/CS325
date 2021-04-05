#include <iostream>
#include <string>
using namespace std;

/**********************************
* define function below here
**********************************/
void Push(string &stack, char item)
{
	if (stack.length() < 100)
	{
		stack += item;
	}
}

bool IsEmpty(const string &stack)
{
	if (stack.length() == 0)
	{
		return true;
	}
	return false;
}

char Top(const string &stack)
{
	if (stack.length() != 0)
	{
		return stack[stack.length() - 1];
	}
	throw "Empty Stack";
}
/*********************************
* define function above here
*********************************/

int main()
{
	return 0;
}