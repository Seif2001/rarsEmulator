#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Register.cpp"

using namespace std;

vector<string> load_data(string filePath)
{
	ifstream file;
	file.open(filePath);
	vector<string> vecOfCode;
	string s;
	if (file.is_open())
	{

		while (file)
		{
			getline(file, s, '\n');
			vecOfCode.push_back(s);
		}
	}

	return vecOfCode;
}
int toInteger(string x)
{
	int newint = std::stoi(x, nullptr, 2);
	return newint;
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

void FigureOut(string currentline, int &pc) // we pass pc by reference since some functions will want to edit the pc counter
{
	if (currentline.find(':') != std::string::npos)
	{
		return; // if the sentence has a : then it doesnt have a function as per seif's handling
	}
	vector<string> sentence;
	string word = "";
	/*
	The upcoming for loop just takes the line and splits it into pieces for example take addi x7, x3, x4 then we have
	[addi, x7, x4, x4] -> array ie, first element is the function remainaing is register or the jump label or immediate or whatever
	if we have lw x3, 0(x4) it turns it into
	[lw x3, 0, x4]
	*/
	for (auto x : currentline)
	{
		if (x == ' ' || x == ',' || x == '(')
		{
			sentence.push_back(word);
			word = "";
		}
		else
		{
			if (x == ')')
			{
				continue;
			}
			word = word + x;
		}
	}
	sentence.push_back(word); // the first element is the function name
	string function = sentence[0];
	if (function == "lw")
	{
		// lw(sentence,&pc);
	}
	else
	{
		cout << "no";
	}
}

string validate(string &line)
{
	string label = "";
	int index = line.find(':');
	if (index != string::npos)
	{
		label = line.substr(0, index + 1);
		line = line.substr(index + 2, line.length() - 1);
	}

	return label;
}

int main()
{
	Register x;
	x.setregistervalue("x0", 4);
	string filename;
	cout << "Enter the name of the file: ";
	cin >> filename;
	vector<string> AssemCodeLines;
	AssemCodeLines = load_data(filename);
	for (int i = 0; i < AssemCodeLines.size(); i++)
	{
		string label = validate(AssemCodeLines[i]);
		if (label.length() > 0)
		{
			AssemCodeLines.insert(AssemCodeLines.begin() + i, label);
		}
	}
	int i = 0;
	cout << "Enter initial PC counter: ";
	cin >> i;
	while (i <= AssemCodeLines.size())
	{
		FigureOut(AssemCodeLines[i], i);
		i++;
	}
	cout << toBinary(-121);
	return 0;
}
