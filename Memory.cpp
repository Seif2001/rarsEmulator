#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>



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
	void load_memValues(string filePath) {

		ifstream file;
		file.open(filePath);
		string s = "";
		while (file) {
			getline(file, s, '\n');
			try {
				
				int address = stoi(s.substr(0, s.find(',')));
				int value = stoi(s.substr(s.find(',') + 1));
				addressMap[address] = value;
			}
			catch(exception e){
				cout << "Format Error in the following line: " << s << endl;
			}
		}
	}
	~Memory()
	{
	}
};
