#pragma once
#include <iostream>
#include <map>

using namespace std;

class Memory
{

private:
	map<int, int> addressMap;

public:
	Memory()
	{
	}
	int getAddressValue(int address)
	{
		return addressMap[address];
	}
	void setAddressValue(int address, int value)
	{
		addressMap[address] = value;
	}
	void print()
	{
		cout << "\nMemory: \n";
		for (auto it = addressMap.cbegin(); it != addressMap.cend(); ++it)
		{
			cout << "Address: " << it->first << " Value: " << it->second << "\n";
		}
		cout << endl;
	}

	~Memory()
	{
	}
};
