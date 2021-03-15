#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <cmath>
using namespace std;

// fixed sizes
const int DATA_SIZE = 32;
const int ADDRESS_SIZE = 12;
const int CONTROL_SIZE = 8;

class Bus
{
private:
	bool data[DATA_SIZE];
	bool address[ADDRESS_SIZE];
	bool control[CONTROL_SIZE];

	// copy constructor
	Bus(const Bus &obj);

	// overloaded assignment operator
	Bus &operator=(const Bus &rhs);

	// overloaded ostream operator
	friend ostream &operator<<(ostream &out, Bus &bus)
	{
		out << "   data: ";
		// converts data array to binary string
		for (int i = 0; i < DATA_SIZE; i++)
		{
			out << bus.getDataBit(i);
		}
		out << endl;

		out << "address: ";
		// converts address array to binary string
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			out << bus.getAddressBit(i);
		}
		out << endl;

		out << "control: ";
		// converts control array to binary string
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			out << bus.getControlBit(i);
		}
		out << endl;
	}

public:
	// default constructor
	Bus()
	{
		// assigns false to data
		for (int i = 0; i < DATA_SIZE; i++)
		{
			data[i] = false;
		}
		// assigns false to address
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			address[i] = false;
		}
		// assigns false to control
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			control[i] = false;
		}
	}

	// data accessor
	bool &getDataBit(int dataIndex)
	{
		// checks for invalid data index
		if (dataIndex < 0 || dataIndex >= DATA_SIZE)
		{
			throw out_of_range("invalid data index");
		}
		return data[dataIndex];
	}
	// address accessor
	bool &getAddressBit(int addressIndex)
	{
		// checks for invalid address index
		if (addressIndex < 0 || addressIndex >= ADDRESS_SIZE)
		{
			throw out_of_range("invalid address index");
		}
		return address[addressIndex];
	}
	// control accessor
	bool &getControlBit(int controlIndex)
	{
		// checks for invalid control index
		if (controlIndex < 0 || controlIndex >= CONTROL_SIZE)
		{
			throw out_of_range("invalid control index");
		}
		return control[controlIndex];
	}

	// returns data as a string
	string getDataString()
	{
		string dataString = "";
		// converts data to string bit-by-bit
		for (int i = 0; i < DATA_SIZE; i++)
		{
			dataString += to_string(getDataBit(i));
		}
		return dataString;
	}
	// sets data to dataString
	void setDataString(string dataString)
	{
		// verifies and assigns the first DATA_SIZE bits of dataString
		for (int i = 0; i < DATA_SIZE; i++)
		{
			if (dataString[i] == '0')
			{
				getDataBit(i) = false;
			}
			else if (dataString[i] == '1')
			{
				getDataBit(i) = true;
			}
			else
			{
				throw invalid_argument("invalid data bit");
			}
		}
	}

	// returns address as a decimal int
	int getAddressInt()
	{
		int addressInt = 0;
		// converts address to decimal bit-by-bit
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			if (getAddressBit(i))
			{
				addressInt += pow(2, (ADDRESS_SIZE - 1 - i));
			}
		}
		return addressInt;
	}
	// sets address to addressString
	void setAddressString(string addressString)
	{
		// verifies and assigns the first ADDRESS_SIZE bits of addressString
		for (int i = 0; i < ADDRESS_SIZE; i++)
		{
			if (addressString[i] == '0')
			{
				getAddressBit(i) = false;
			}
			else if (addressString[i] == '1')
			{
				getAddressBit(i) = true;
			}
			else
			{
				throw invalid_argument("invalid address bit");
			}
		}
	}

	// returns control as a string
	string getControlString()
	{
		string controlString = "";
		// converts control to string bit-by-bit
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			controlString += to_string(getControlBit(i));
		}
		return controlString;
	}
	// sets control to controlString
	void setControlString(string controlString)
	{
		// verifies and assigns the first CONTROL_SIZE bits of controlString
		for (int i = 0; i < CONTROL_SIZE; i++)
		{
			if (controlString[i] == '0')
			{
				getControlBit(i) = false;
			}
			else if (controlString[i] == '1')
			{
				getControlBit(i) = true;
			}
			else
			{
				throw invalid_argument("invalid control bit");
			}
		}
	}

	// destructor
	~Bus() {}
};

#endif