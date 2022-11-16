#pragma once
#include <iostream>
#include <map>

using namespace std;

class Register
{

private:
	map<string, int> reg;

public:
	Register()
	{
		reg["x0"] = 0;
		reg["x1"] = 0;
		reg["x2"] = 0;
		reg["x3"] = 0;
		reg["x4"] = 0;
		reg["x5"] = 0;
		reg["x6"] = 0;
		reg["x7"] = 0;
		reg["x8"] = 0;
		reg["x9"] = 0;
		reg["x10"] = 0;
		reg["x11"] = 0;
		reg["x12"] = 0;
		reg["x13"] = 0;
		reg["x14"] = 0;
		reg["x15"] = 0;
		reg["x16"] = 0;
		reg["x17"] = 0;
		reg["x18"] = 0;
		reg["x19"] = 0;
		reg["x20"] = 0;
		reg["x21"] = 0;
		reg["x22"] = 0;
		reg["x23"] = 0;
		reg["x24"] = 0;
		reg["x25"] = 0;
		reg["x26"] = 0;
		reg["x27"] = 0;
		reg["x28"] = 0;
		reg["x29"] = 0;
		reg["x30"] = 0;
		reg["x31"] = 0;
	}
	string convName2X(string name)
	{
		if (name[0] == 'x')
		{
			return name;
		}
		else
		{
			if (name == "zero")
			{
				return "x0";
			}
			if (name == "ra")
			{
				return "x1";
			}
			else if (name == "sp")
			{
				return "x2";
			}
			else if (name == "gp")
			{
				return "x3";
			}
			else if (name == "tp")
			{
				return "x4";
			}
			else if (name == "t0")
			{
				return "x5";
			}
			else if (name == "t1")
			{
				return "x6";
			}
			else if (name == "t2")
			{
				return "x7";
			}
			else if (name == "s0" || name == "fp")
			{
				return "x8";
			}
			else if (name == "s1")
			{
				return "x9";
			}
			else if (name == "a0")
			{
				return "x10";
			}
			else if (name == "a1")
			{
				return "x11";
			}
			else if (name == "a2")
			{
				return "x12";
			}
			else if (name == "a3")
			{
				return "x13";
			}
			else if (name == "a4")
			{
				return "x14";
			}
			else if (name == "a5")
			{
				return "x15";
			}
			else if (name == "a6")
			{
				return "x16";
			}
			else if (name == "a7")
			{
				return "x17";
			}
			else if (name == "s2")
			{
				return "x18";
			}
			else if (name == "s3")
			{
				return "x19";
			}
			else if (name == "s4")
			{
				return "x20";
			}
			else if (name == "s5")
			{
				return "x21";
			}
			else if (name == "s6")
			{
				return "x22";
			}
			else if (name == "s7")
			{
				return "x23";
			}
			else if (name == "s8")
			{
				return "x24";
			}
			else if (name == "s9")
			{
				return "x25";
			}
			else if (name == "s10")
			{
				return "x26";
			}
			else if (name == "s11")
			{
				return "x27";
			}
			else if (name == "t3")
			{
				return "x28";
			}
			else if (name == "t4")
			{
				return "x29";
			}
			else if (name == "t5")
			{
				return "x30";
			}
			else if (name == "t6")
			{
				return "x31";
			}
			else
			{
				return name;
			}
		}
	}
	bool checkReg(string &name)
	{
		name = convName2X(name);
		if (reg.find(name) == reg.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	int getregistervalue(string name)
	{
		return reg[name];
	}
	void setregistervalue(string name, int x)
	{
		name = convName2X(name);
		// we have to put the if "it is found" here
		reg[name] = x;
	}
	void print()
	{
		cout << "\nRegisters: \n";
		for (auto it = reg.cbegin(); it != reg.cend(); ++it)
		{
			cout << "Register: " << it->first << " Value: " << it->second << "\n";
		}
		cout << endl;
	}

	~Register()
	{
	}
};
