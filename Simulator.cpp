#include<iostream>
#include<vector>

using namespace std;

class Simulator
{
private:
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

	~Simulator()
	{
	}

};
