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
	}
	int getPc() {
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

	void JumptoBranch(string label) {
		label = label + ":";
		for (int i = 0; i < rawCode.size(); i++) {
			if (rawCode[i] == label) {
				//i = i * 4;
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

		else if (currFunction == "and" && line.size() == 4) // I added the line size because if its less or more the user put more or less stuff which is invalid
		{
			andd();
		}
		else if (currFunction == "andi" && line.size() == 4)
		{
			andi();
		}
		else if (currFunction == "sltu" && line.size() == 4)
		{
			sltu();
		}
		else if (currFunction == "sll" && line.size() == 4)
		{
			sll();
		}
		else if (currFunction == "sra" && line.size() == 4)
		{
			sra();
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
		else if (currFunction == "or" && line.size() == 4)
		{
			orr();
		}
		else if (currFunction == "bne" && line.size() == 4) {
			bne();
		}
		else
		{
			cout << "That function doesnt exist, or you wrote it wrong!\n";
		}
		allRegisters.print();
		allMemory.print();
	}

	void bne() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			if (allRegisters.getregistervalue(line[1]) != allRegisters.getregistervalue(line[2])) {
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
	void auipc(int &pc)
	{
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

	void lui() {
		if (allRegisters.checkReg(line[1]))
		{
			string result;
			string t2 = toBinary(allRegisters.getregistervalue(line[2]));
			if (allRegisters.getregistervalue(line[2]) < 0) t2 = twosComp(t2);
			for (int i = 0; i < 20; i++) {
				result[i] = t2[i];
			}
			for (int i = 20; i < 32; i++) {
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

	void jal () {
		if (allRegisters.checkReg(line[1]))
		{
			allRegisters.setregistervalue(line[1], pc + 4);
			JumptoBranch(line[2]);
		}
		else
		{
			exit(0);
		}
	}

	void jalr() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[3]))
		{
			allRegisters.setregistervalue(line[1], pc + 4);
			int offset = stoi(line[2]);
			int t1 = allRegisters.getregistervalue(line[3]) + offset;
			pc = t1;
		}
		else
		{
			exit(0);
		}
	}
	
	void bge() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			int t1 = allRegisters.getregistervalue(line[1]);
			int t2 = allRegisters.getregistervalue(line[2]);
			string label = line[3];
			if (t1 >= t2) {
				JumptoBranch(label);
			}
		}
		else
		{
			exit(0);
		}
	}

	void bltu() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{
			
			int t1 = abs(allRegisters.getregistervalue(line[1]));
			int t2 = abs(allRegisters.getregistervalue(line[2]));
			string label = line[3];
			if (t1 < t2) {
				JumptoBranch(label);
			}
		}
		else
		{
			exit(0);
		}
	}

	void bgeu() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			int t1 = abs(allRegisters.getregistervalue(line[1]));
			int t2 = abs(allRegisters.getregistervalue(line[2]));
			string label = line[3];
			if (t1 >= t2) {
				JumptoBranch(label);
			}
		}
		else
		{
			exit(0);
		}
	}

	void xori() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			string t1 = toBinary(allRegisters.getregistervalue(line[2]));
			string t2 = toBinary(allRegisters.getregistervalue(line[3]));
			string t3 = "";
			if (allRegisters.getregistervalue(line[2]) < 0) t1 = twosComp(t1);
			if (allRegisters.getregistervalue(line[3]) < 0) t2 = twosComp(t2);
			for (int i = 0; i < t1.size(); i++) {
				if (t1[i] == t2[i]) t3 += "0";
				else t3 += "1";
			}
			int result = toInteger(t3);
			allRegisters.setregistervalue(line[1],result);
			pc++;
		}
		else
		{
			exit(0);
		}
	}

	void ori() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			string t1 = toBinary(allRegisters.getregistervalue(line[2]));
			string t2 = toBinary(allRegisters.getregistervalue(line[3]));
			string t3 = "";
			if (allRegisters.getregistervalue(line[2]) < 0) t1 = twosComp(t1);
			if (allRegisters.getregistervalue(line[3]) < 0) t2 = twosComp(t2);
			for (int i = 0; i < t1.size(); i++) {
				if (t1[i] == '1' || t2[i] == '1') t3 += "1";
				else t3 += "0";
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

	void add() {
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

	void sub() {
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

	void xorr() {
		if (allRegisters.checkReg(line[1]) && allRegisters.checkReg(line[2]))
		{

			string t1 = toBinary(allRegisters.getregistervalue(line[2]));
			string t2 = toBinary(allRegisters.getregistervalue(line[3]));
			string t3 = "";
			if (allRegisters.getregistervalue(line[2]) < 0) t1 = twosComp(t1);
			if (allRegisters.getregistervalue(line[3]) < 0) t2 = twosComp(t2);
			for (int i = 0; i < t1.size(); i++) {
				if (t1[i] == t2[i]) t3 += "0";
				else t3 += "1";
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
	~Simulator()
	{
	}
};
