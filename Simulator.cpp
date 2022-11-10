#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Simulator
{
private:
	Register allRegisters;
	vector<string> line;

public:
	Simulator()
	{
	}

	Simulator(vector<string> line)
	{
		this->line = line;
	}

	void Setline(vector<string> line)
	{
		this->line = line;
	}
	void ChooseFunc(int &pc)
	{
		string currFunction = line[0];
		if (currFunction == "and" && line.size() == 4) // I added the line size because if its less or more the user put more or less stuff which is invalid
		{
			andd();
		}
		else if (currFunction == "andi" && line.size() == 4)
		{
			andi();
		}
		else
		{
			cout << "That function doesnt exist, or you wrote it wrong!\n";
		}
		allRegisters.print();
	}
	void andd()
	{
		int result = allRegisters.getregistervalue(line[2]) & allRegisters.getregistervalue(line[3]);
		allRegisters.setregistervalue(line[1], result);
	}
	void andi()
	{
		int result = allRegisters.getregistervalue(line[2]) & stoi(line[3]);
		allRegisters.setregistervalue(line[1], result);
	}
	void auipc(int &pc)
	{
	}
	~Simulator()
	{
	}
};
