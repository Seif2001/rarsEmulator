#include <iostream>
#include <vector>
#include <string>
#include <math.h>
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
	int const initialpc;
	int pc;

public:
	Simulator(vector<string> rawCode, int pc) : initialpc(pc)
	{
		this->rawCode = rawCode;
		this->pc = pc;
		allMemory.setAddressValue(0, -65537);
		allMemory.setAddressValue(1, 537);
	}
	int getPc()
	{
		return pc;
	}
	string twosComp(string x)
	{
		int i, carr = 1;
		for (i = 0; i < x.size(); i++)
		{
			x[i] = x[i] == '0' ? '1' : '0';
		}
		for (i = x.size() - 1; i >= 0; i--)
		{
			if (x[i] == '1' && carr == 1)
			{
				x[i] = '0';
			}
			else if (x[i] == '0' && carr == 1)
			{
				x[i] = '1';
				carr = 0;
			}
		}
		return x;
	}
	int toInteger(string x)
	{
		int num = 0;
		int k = 0;
		string curr = "";
		bool isNegative = false;
		curr += x[0];
		if (curr == "1")
		{
			isNegative = true;
			x = twosComp(x);
		}
		for (int i = x.length() - 1; i >= 0; i--)
		{
			string curr = "";
			curr += x[i];
			if (i != 0)
			{
				num += pow(2, k++) * stoi(curr);
			}
		}
		if (isNegative)
		{
			num *= -1;
		}
		return num;
	}
	int toIntegerunsigned(string x)
	{
		int num = 0;
		int k = 0;
		string curr = "";
		curr += x[0];
		for (int i = x.length() - 1; i >= 0; i--)
		{
			string curr = "";
			curr += x[i];
			if (i != 0)
			{
				num += pow(2, k++) * stoi(curr);
			}
		}
		return num;
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

	void JumptoBranch(string label)
	{
		label = label + ":";
		for (int i = 0; i < rawCode.size(); i++)
		{
			if (rawCode[i] == label)
			{
				// i = i * 4;
				pc = i;
				break;
			}
		}
	}

	void Setline(vector<string> line)
	{
		this->line = line;
	}
	void ChooseFunc()
	{
		string currFunction = line[0];
		if (currFunction.find(":") != std::string::npos) // if we have a collon we skip since its just a label with nothing else
		{
			pc++;
			return;
		}

		else if (currFunction == "addi" && line.size() == 4)
		{
			addi();
		}
		else if (currFunction == "and" && line.size() == 4) // I added the line size because if its less or more the user put more or less stuff which is invalid
		{
			andd();
		}
		else if (currFunction == "andi" && line.size() == 4)
		{
			andi();
		}
		else if (currFunction == "auipc" && line.size() == 3)
		{
			auipc();
		}
		else if (currFunction == "bge" && line.size() == 4)
		{
			bge();
		}
		else if (currFunction == "bgeu" && line.size() == 4)
		{
			bgeu();
		}
		else if (currFunction == "blt" && line.size() == 4)
		{
			blt();
		}
		else if (currFunction == "bltu" && line.size() == 4)
		{
			bltu();
		}
		else if (currFunction == "bne" && line.size() == 4)
		{
			bne();
		}
		else if ((currFunction == "ebreak" || currFunction == "ecall") && line.size() == 1)
		{
			exit(0);
		}
		else if (currFunction == "fence" && line.size() == 3)
		{
			exit(0);
		}
		else if (currFunction == "jal" && line.size() == 3)
		{
			jal();
		}
		else if (currFunction == "jalr" && line.size() == 4)
		{
			jalr();
		}
		else if (currFunction == "lb" && line.size() == 4)
		{
			lb();
		}
		else if (currFunction == "lbu" && line.size() == 4)
		{
			lbu();
		}
		else if (currFunction == "lh" && line.size() == 4)
		{
			lh();
		}
		else if (currFunction == "lhu" && line.size() == 4)
		{
			lhu();
		}
		else if (currFunction == "lui" && line.size() == 3)
		{
			lui();
		}
		else if (currFunction == "lw" && line.size() == 4)
		{
			lw();
		}
		else if (currFunction == "or" && line.size() == 4)
		{
			orr();
		}
		else if (currFunction == "sh" && line.size() == 4)
		{
			sh();
		}
		else if (currFunction == "sll" && line.size() == 4)
		{
			sll();
		}
		else if (currFunction == "slli" && line.size() == 4)
		{
			slli();
		}
		else if (currFunction == "slt" && line.size() == 4)
		{
			slt();
		}
		else if (currFunction == "slti" && line.size() == 4)
		{
			slti();
		}
		else if (currFunction == "sltiu" && line.size() == 4)
		{
			sltiu();
		}
		else if (currFunction == "sltu" && line.size() == 4)
		{
			sltu();
		}
		else if (currFunction == "sra" && line.size() == 4)
		{
			sra();
		}
		else if (currFunction == "srai" && line.size() == 4)
		{
			srai();
		}
		else if (currFunction == "srl" && line.size() == 4)
		{
			srl();
		}
		else if (currFunction == "srli" && line.size() == 4)
		{
			srli();
		}
		else if (currFunction == "sw" && line.size() == 4)
		{
			sw();
		}

		else
		{
			cout << "That function doesnt exist, or you wrote it wrong!\n";
			exit(0);
		}
		allRegisters.print();
		allMemory.print();
	}

	// Instructions:

	void add()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int t2 = allRegisters.getregistervalue(line[2]);
			int t3 = allRegisters.getregistervalue(line[3]);
			int t1 = t2 + t3;
			allRegisters.setregistervalue(line[1], t1);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void addi()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int result = allRegisters.getregistervalue(line[2]) + stoi(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void andd()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = allRegisters.getregistervalue(line[2]) & allRegisters.getregistervalue(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
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
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void auipc()
	{
		if (allRegisters.checkReg(line[1]))
		{
			int result = pc * 4 + (stoi(line[2]) << 12);
			allRegisters.setregistervalue(line[2], result);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void bge()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int t1 = allRegisters.getregistervalue(line[1]);
			int t2 = allRegisters.getregistervalue(line[2]);
			string label = line[3];
			if (t1 >= t2)
			{
				JumptoBranch(label);
			}
			else
			{
				pc++;
			}
		}
		else
		{
			exit(0);
		}
	}

	void bgeu()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			string unsignedt1;
			string unsignedt2;
			int t1 = allRegisters.getregistervalue(line[1]);
			int t2 = allRegisters.getregistervalue(line[2]);
			if (t1 < 0)
			{
				unsignedt1 = toBinary(t1);
				t1 = toIntegerunsigned(unsignedt1);
			}
			if (t2 < 0)
			{
				unsignedt2 = toBinary(t2);
				t2 = toIntegerunsigned(unsignedt2);
			}
			string label = line[3];
			if (t1 >= t2)
			{
				JumptoBranch(label);
			}
			else
			{
				pc++;
			}
		}
		else
		{
			exit(0);
		}
	}

	void blt()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			if (allRegisters.getregistervalue(line[1]) < allRegisters.getregistervalue(line[2]))
			{
				JumptoBranch(line[3]);
			}
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void bltu()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			string unsignedt1;
			string unsignedt2;
			int t1 = allRegisters.getregistervalue(line[1]);
			int t2 = allRegisters.getregistervalue(line[2]);
			string label = line[3];
			if (t1 < 0)
			{
				unsignedt1 = toBinary(t1);
				t1 = toIntegerunsigned(unsignedt1);
			}
			if (t2 < 0)
			{
				unsignedt2 = toBinary(t2);
				t2 = toIntegerunsigned(unsignedt2);
			}
			if (t1 < t2)
			{
				JumptoBranch(label);
			}
			else
			{
				pc++;
			}
		}
		else
		{
			exit(0);
		}
	}

	void bne()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			if (allRegisters.getregistervalue(line[1]) != allRegisters.getregistervalue(line[2]))
			{
				JumptoBranch(line[3]);
			}
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void jal()
	{
		if (allRegisters.checkReg(line[1]))
		{
			allRegisters.setregistervalue(line[1], pc + 1);
			JumptoBranch(line[2]);
		}
		else
		{
			exit(0);
		}
	}

	void jalr()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			allRegisters.setregistervalue(line[1], pc + 1);
			int offset = stoi(line[2]);
			int t1 = allRegisters.getregistervalue(line[3]) + offset;
			pc = t1;
		}
		else
		{
			exit(0);
		}
	}

	void lb()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int offset = stoi(line[2]);
			int t2 = allRegisters.getregistervalue(line[3]) + offset;
			string t1 = toBinary(allMemory.getAddressValue(t2));
			string bword = "";
			int j = 0;
			for (int i = 24; i <= 31; i++)
			{
				bword += t1[i];
			}
			int t = toInteger(bword);
			t1 = toBinary(t);
			t = toInteger(t1);
			allRegisters.setregistervalue(line[1], t);
			pc++;
		}
		else
		{
			exit(0);
		}
	}
	void lbu()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int offset = stoi(line[2]);
			int t2 = allRegisters.getregistervalue(line[3]) + offset;
			string t1 = toBinary(allMemory.getAddressValue(t2));
			string bword = "";
			int j = 0;
			for (int i = 24; i <= 31; i++)
			{
				bword += t1[i];
			}
			int t = toInteger(bword);
			t1 = toBinary(t);
			t = toInteger(t1);
			allRegisters.setregistervalue(line[1], t);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void lh()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int result = allMemory.getAddressValue(stoi(line[2]) + allRegisters.getregistervalue(line[3]));
			bool flag = false;
			if (result < 0)
			{
				flag = true;
			}
			result = abs(result);
			string binRes = toBinary(result);
			if (binRes.length() <= 16)
			{
				result = result * pow(-1, flag);
			}
			else
			{
				binRes = binRes.substr(binRes.length() - 16, 16);
				result = toInteger(binRes) * pow(-1, flag);
			}
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void lhu()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int result = allMemory.getAddressValue(stoi(line[2]) + allRegisters.getregistervalue(line[3]));
			bool flag = false;
			if (result < 0)
			{
				flag = true;
			}
			result = abs(result);
			string binRes = toBinary(result);
			if (binRes.length() <= 16)
			{
				result = result * pow(-1, flag);
			}
			else
			{
				binRes = binRes.substr(binRes.length() - 16, 16);
				result = (unsigned)(toInteger(binRes) * pow(-1, flag));
			}
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void lui()
	{ // not wokring
		if (allRegisters.checkReg(line[1]))
		{
			string result;
			string t2 = toBinary(stoi(line[2]));
			if (allRegisters.getregistervalue(line[2]) < 0)
				t2 = twosComp(t2);
			for (int i = 0; i < 20; i++)
			{
				result += t2[i];
			}
			for (int i = 20; i < 32; i++)
			{
				result[i] = '0';
			}
			int res = toInteger(result);
			allRegisters.setregistervalue(line[1], res);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void lw()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int result = allMemory.getAddressValue(stoi(line[2]) + allRegisters.getregistervalue(line[3]));
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void ori()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			string t1 = toBinary(allRegisters.getregistervalue(line[2]));
			string t2 = toBinary(allRegisters.getregistervalue(line[3]));
			string t3 = "";
			if (allRegisters.getregistervalue(line[2]) < 0)
				t1 = twosComp(t1);
			if (allRegisters.getregistervalue(line[3]) < 0)
				t2 = twosComp(t2);
			for (int i = 0; i < t1.size(); i++)
			{
				if (t1[i] == '1' || t2[i] == '1')
					t3 += "1";
				else
					t3 += "0";
			}
			int result = toInteger(t3);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void orr()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = allRegisters.getregistervalue(line[2]) | allRegisters.getregistervalue(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sb()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int address = ((stoi(line[2])) + allRegisters.getregistervalue(line[3]));
			int value = allRegisters.getregistervalue(line[1]);
			bool flag = false;
			if (value < 0)
			{
				flag = true;
			}
			value = abs(value);
			string binRes = toBinary(value);
			if (binRes.length() <= 8)
			{
				value = value * pow(-1, flag);
			}
			else
			{
				binRes = binRes.substr(binRes.length() - 8, 8);
				value = toInteger(binRes) * pow(-1, flag);
			}
			allMemory.setAddressValue(address, value);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sh()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int address = ((stoi(line[2])) + allRegisters.getregistervalue(line[3]));
			int value = allRegisters.getregistervalue(line[1]);
			bool flag = false;
			if (value < 0)
			{
				flag = true;
			}
			value = abs(value);
			string binRes = toBinary(value);
			if (binRes.length() <= 16)
			{
				value = value * pow(-1, flag);
			}
			else
			{
				binRes = binRes.substr(binRes.length() - 16, 16);
				value = toInteger(binRes) * pow(-1, flag);
			}
			allMemory.setAddressValue(address, value);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sll()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = allRegisters.getregistervalue(line[2]) << allRegisters.getregistervalue(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
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
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void slt()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int value = allRegisters.getregistervalue(line[2]) < allRegisters.getregistervalue(line[3]) ? 1 : 0;
			allRegisters.setregistervalue(line[1], value);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void slti()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int value = allRegisters.getregistervalue(line[2]) < stoi(line[3]) ? 1 : 0;
			allRegisters.setregistervalue(line[1], value);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sltiu()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int value = allRegisters.getregistervalue(line[2]) < abs(stoi(line[3])) ? 1 : 0;
			allRegisters.setregistervalue(line[1], value);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sltu()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = (unsigned)allRegisters.getregistervalue(line[2]) < (unsigned)allRegisters.getregistervalue(line[3]) ? 1 : 0;
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sra()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int LHS = allRegisters.getregistervalue(line[2]);
			int RHS = allRegisters.getregistervalue(line[3]);
			int result = 0;
			if (LHS < 0 && RHS > 0)
			{
				result = LHS >> RHS | ~(~0U >> RHS);
			}
			else
			{
				result = LHS >> RHS;
			}
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void srai()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int result = allRegisters.getregistervalue(line[2]) >> stoi(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void srl()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int result = allRegisters.getregistervalue(line[2]) >> allRegisters.getregistervalue(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}
	void srli()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int result = (unsigned)allRegisters.getregistervalue(line[2]) >> stoi(line[3]);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void sub()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]) && allRegisters.checkReg(line[3]))
		{
			int t2 = allRegisters.getregistervalue(line[2]);
			int t3 = allRegisters.getregistervalue(line[3]);
			int t1 = t2 - t3;
			allRegisters.setregistervalue(line[1], t1);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void sw()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			int address = ((stoi(line[2])) + allRegisters.getregistervalue(line[3]));
			int value = allRegisters.getregistervalue(line[1]);
			allMemory.setAddressValue(address, value);
			pc++;
		}
		else
		{
			cout << "This line contains an error please fix it.\nExiting.\n";
			exit(0);
		}
	}

	void xorr()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			string t1 = toBinary(allRegisters.getregistervalue(line[2]));
			string t2 = toBinary(allRegisters.getregistervalue(line[3]));
			string t3 = "";
			if (allRegisters.getregistervalue(line[2]) < 0)
				t1 = twosComp(t1);
			if (allRegisters.getregistervalue(line[3]) < 0)
				t2 = twosComp(t2);
			for (int i = 0; i < t1.size(); i++)
			{
				if (t1[i] == t2[i])
					t3 += "0";
				else
					t3 += "1";
			}
			int result = toInteger(t3);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void xori()
	{
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			string t1 = toBinary(allRegisters.getregistervalue(line[2]));
			string t2 = toBinary(allRegisters.getregistervalue(line[3]));
			string t3 = "";
			if (allRegisters.getregistervalue(line[2]) < 0)
				t1 = twosComp(t1);
			if (allRegisters.getregistervalue(line[3]) < 0)
				t2 = twosComp(t2);
			for (int i = 0; i < t1.size(); i++)
			{
				if (t1[i] == t2[i])
					t3 += "0";
				else
					t3 += "1";
			}
			int result = toInteger(t3);
			allRegisters.setregistervalue(line[1], result);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	~Simulator()
	{
	}
};
