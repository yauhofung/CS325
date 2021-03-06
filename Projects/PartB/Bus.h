#ifndef BUS_H
#define BUS_H

using namespace std;

// fixed size
const int SIZE = 32;

class Bus
{
private:
	bool data[SIZE];
	bool address[SIZE];
	bool control[SIZE];

	// copy constructor
	Bus(const Bus &obj);

	// overloaded assignment operator
	Bus &operator=(const Bus &rhs);

	// overloaded ostream operator
	friend ostream &operator<<(ostream &out, Bus &bus)
	{
		out << "   data: ";
		// converts data array to binary string
		for (int i = 0; i < SIZE; i++)
		{
			out << bus.data[i];
		}
		out << endl;

		out << "address: ";
		// converts address array to binary string
		for (int i = 0; i < SIZE; i++)
		{
			out << bus.address[i];
		}
		out << endl;

		out << "control: ";
		// converts control array to binary string
		for (int i = 0; i < SIZE; i++)
		{
			out << bus.control[i];
		}
		out << endl;
	}

public:
	// default constructor
	Bus()
	{
		// assigns false to all lines
		for (int i = 0; i < SIZE; i++)
		{
			data[i] = false;
			address[i] = false;
			control[i] = false;
		}
	}

	// data accessor
	bool &getData(int dataIndex)
	{
		// checks for invalid data index
		if (dataIndex < 0 || dataIndex >= SIZE)
		{
			throw "invalid data index";
		}
		return data[dataIndex];
	}
	// address accessor
	bool &getAddress(int addressIndex)
	{
		// checks for invalid address index
		if (addressIndex < 0 || addressIndex >= SIZE)
		{
			throw "invalid address index";
		}
		return address[addressIndex];
	}
	// control accessor
	bool &getControl(int controlIndex)
	{
		// checks for invalid control index
		if (controlIndex < 0 || controlIndex >= SIZE)
		{
			throw "invalid control index";
		}
		return control[controlIndex];
	}

	// destructor
	~Bus() {}
};

#endif