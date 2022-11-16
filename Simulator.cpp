#include <iostream>
#include <vector>
#include <string>
#include "Memory.cpp"
#include "Register.cpp"

using namespace std;

class Simulator
{
private:
	Register allRegisters;
	Memory allMemory;
	vector<string> rawCode;
	vector<string> line;

public:
	Simulator(vector<string> rawCode)
	{
		this->rawCode = rawCode;
	}

	void Setline(vector<string> line)
	{
		this->line = line;
	}
	void ChooseFunc(int &pc)
	{
		string currFunction = line[0];
		if (currFunction.find(":") != std::string::npos) // if we have a collon we skip since its just a label with nothing else
		{
			return;
		}

		else if (currFunction == "and" && line.size() == 4) // I added the line size because if its less or more the user put more or less stuff which is invalid
		{
			andd();
		}
		else if (currFunction == "andi" && line.size() == 4)
		{
			andi();
		}
		else if (currFunction == "sll" && line.size() == 4)
		{
			sll();
		}
		else if (currFunction == "slli" && line.size() == 4)
		{
			slli();
		}
		else if (currFunction == "lw" && line.size() == 4)
		{
			lw();
		}
		else if (currFunction == "addi" && line.size() == 4)
		{
			addi();
		}
		else
		{
			cout << "That function doesnt exist, or you wrote it wrong!\n";
		}
		allRegisters.print();
		allMemory.print();
	}
	void andd()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = allRegisters.getregistervalue(line[2]) & allRegisters.getregistervalue(line[3]);
			allRegisters.setregistervalue(line[1], result);
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void addi()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int result = allRegisters.getregistervalue(line[2]) + stoi(line[3]);
			allRegisters.setregistervalue(line[1], result);
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void andi()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int result = allRegisters.getregistervalue(line[2]) & stoi(line[3]);
			allRegisters.setregistervalue(line[1], result);
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void auipc(int &pc)
	{
	}
	void sll()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = allRegisters.getregistervalue(line[2]) << allRegisters.getregistervalue(line[3]);
			allRegisters.setregistervalue(line[1], result);
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void slli()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int result = allRegisters.getregistervalue(line[2]) << stoi(line[3]);
			allRegisters.setregistervalue(line[1], result);
			cout << line[1] << " " << result;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void lw()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int result = allMemory.getAddressValue(stoi(line[2]) + allRegisters.getregistervalue(line[3]));
			allRegisters.setregistervalue(line[1], result);
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	~Simulator()
	{
	}
};
