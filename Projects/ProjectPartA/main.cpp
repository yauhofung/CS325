#include "Log.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Log log;

	log.recordBinaryString("");
	log.recordBinaryString(" ");
	log.recordBinaryString("0 0 0");

	log.recordBinaryString("0");
	log.recordBinaryString("111");
	log.recordBinaryString("10101");

	vector<bool> array = {};
	log.recordBinaryArray(array);

	vector<bool> array1 = {true};
	log.recordBinaryArray(array1);
	vector<bool> array2 = {false, false, false};
	log.recordBinaryArray(array2);
	vector<bool> array3 = {false, true, false, true, false};
	log.recordBinaryArray(array3);

	cout << "Done.\n";
	return 0;
}