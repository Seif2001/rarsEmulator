#pragma once
#include"Register.h"
#include<iostream>
#include<map>

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

	int getregistervalue(string name) {
		return reg[name];
	}


	~Register()
	{
	}
};
