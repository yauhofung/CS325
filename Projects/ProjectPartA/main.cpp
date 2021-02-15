#include "Log.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Log log;

	log.recordBinaryString("000000000000", "");
	log.recordBinaryString("000000000001", " ");
	log.recordBinaryString("000000000010", "0 0 0");

	log.recordBinaryString("000000000011", "0");
	log.recordBinaryString("000000000100", "111");
	log.recordBinaryString("000000000101", "10101");

	vector<bool> array = {};
	log.recordBinaryArray("000000000110", array);

	vector<bool> array1 = {true};
	log.recordBinaryArray("000000000111", array1);
	vector<bool> array2 = {false, false, false};
	log.recordBinaryArray("000000001000", array2);
	vector<bool> array3 = {false, true, false, true, false};
	log.recordBinaryArray("000000001001", array3);

	cout << "Done.\n";
	return 0;
}