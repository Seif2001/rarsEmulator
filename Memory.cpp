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
	string dectohex(int dec)
	{
		stringstream ss;
		ss << hex << dec;
		string res(ss.str());
		return res;
	}
	string dectooct(int dec)
	{
		stringstream ss;
		ss << oct << dec;
		string res(ss.str());
		return res;
	}
	string toBinary(int n)
	{
		string bNum = "";
		for (int i = 31; i >= 0; i--)
		{
			int k = n >> i;
			if (k & 1)
				bNum.push_back('1');
			else
				bNum.push_back('0');
		}
		return bNum;
	}
	void print()
	{
		cout << "\nMemory: \n";
		for (auto it = addressMap.cbegin(); it != addressMap.cend(); ++it)
		{
			cout << setw(10) << left << "Memory: " << setw(3) << left << it->first << setw(8) << left << " Value: " << setw(9) << left << it->second << setw(15) << " HexaDecimal Value: " << setw(10) << dectohex(it->second) << setw(0) << "Octal Value: " << setw(15) << dectooct(it->second) << setw(15) << "Binary Value: " << setw(35) << toBinary(it->second) << "\n";
		}
		cout << endl;
	}
	void load_memValues(string filePath)
	{

		ifstream file;
		file.open(filePath);
		string s = "";
		while (file)
		{
			getline(file, s, '\n');
			try
			{

				int address = stoi(s.substr(0, s.find(',')));
				int value = stoi(s.substr(s.find(',') + 1));
				addressMap[address] = value;
			}
			catch (exception e)
			{
				cout << "Format Error in the following line: " << s << endl;
			}
		}
	}
	~Memory()
	{
	}
};
