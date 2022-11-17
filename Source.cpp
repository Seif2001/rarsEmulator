#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Register.cpp"
#include "Simulator.cpp"
#include "Memory.cpp"

using namespace std;

vector<string> load_data(string filePath)
{
	ifstream file;
	file.open(filePath);
	vector<string> vecOfCode;
	string s = "";
	if (file.is_open())
	{
		while (file)
		{
			getline(file, s, '\n');
			vecOfCode.push_back(s);
		}
	}
	else
	{
		string f = "";
		cout << "Could not find file";
		exit(0);
	}
	vecOfCode.pop_back();

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

vector<string> FigureOut(string currentline, int &pc) // we pass pc by reference since some functions will want to edit the pc counter
{
	vector<string> sentence;
	if (currentline.find(':') != std::string::npos)
	{
		sentence.push_back(currentline);
		return sentence; // if the sentence has a : then it doesnt have a function as per seif's handling
	}
	string word = "";
	/*
	The upcoming for loop just takes the line and splits it into pieces for example take addi x7, x3, x4 then we have
	[addi, x7, x4, x4] -> array ie, first element is the function remainaing is register or the jump label or immediate or whatever
	if we have lw x3, 0(x4) it turns it into
	[lw, x3, 0, x4]
	*/
	for (auto x : currentline)
	{
		if (x == ' ' || x == ',' || x == '(')
		{
			if (word != "")
			{
				sentence.push_back(word);
			}
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
	return sentence;
}

string validate(string &line)
{
	// maybe we'll handle comments idk
	string label = "";
	int index = line.find(':');
	if (index != string::npos)
	{
		label = line.substr(0, index + 1);
		line = line.substr(index + 1, line.length() - 1); // this puts a space after labels but its handled in figureout() just putting this comment incase later on some bug happens
	}

	return label;
}

int main()
{
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
	Simulator sim(AssemCodeLines);
	int i = 0;
	cout << "Enter initial PC counter: ";
	cin >> i;
	i = i / 4;
	cout << AssemCodeLines.size();
	/*pc counter is given in multiples of 4 and
	is incrimented by 4 each time so we just divide by 4 and now in the loop we can incriment by 1
	but we need to multiply by 4 if we need to store pc address for example*/
	while (i < AssemCodeLines.size() && i >= 0)
	{

		sim.Setline(FigureOut(AssemCodeLines[i], i));

		cout << "Executing: " << AssemCodeLines[i] << endl;
		/*
		// dont know if we'll keep this but im just using it for now so it catches if the user
		puts a string instead of an int in the file for example addi x3,x4,omar so we dont have to test every function
		*/
		try
		{
			sim.ChooseFunc(i);
		}
		catch (exception e)
		{
			cout << AssemCodeLines[i] << " Is not valid syntax. Ignoring that line." << endl;
		}
		i++;
	}
	return 0;
}
