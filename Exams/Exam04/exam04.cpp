#include <iostream>
#include <string>

//Helper Function
void Adder(bool a[],bool b[],bool r[],const int n)
{
	bool c = false, cp[n];

	for(int i = n - 1;i >= 0;i -= 1)
	{
		cp[i] = (a[i] ^ b[i]) ^ c;
		c = (a[i] & b[i]) | (a[i] & c) | (b[i] & c);
	}

	for(int i = 0;i < n;i += 1)
	{
		r[i] = cp[i];
	}
}

/******************************************************************************
Question 01
*******************************************************************************
...write solution between these lines...




******************************************************************************/



/******************************************************************************
Question 02
*******************************************************************************/



/******************************************************************************
Question 03
*******************************************************************************
...write solution between these lines...




******************************************************************************/


/******************************************************************************
Question 04
******************************************************************************/


int main()
{
	return 0;
}
