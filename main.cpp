#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> load_data(string filePath) {
	ifstream file;
	file.open(filePath);
	vector<string> vecOfCode;
	string s;
	if (file.is_open()) {
		
		while (file) {
			getline(file,s,'\n');
			vecOfCode.push_back(s);
		}
	}
	
	return vecOfCode;

}

string validate(string &line) {
	string label = "";
	int index = line.find(':');
	if (index != string::npos) {
		label = line.substr(0, index + 1);
		line = line.substr(index+1, line.length() - 1);
	}
	
	return label;
}

int main() {
	vector<string> AssemCodeLines;
	AssemCodeLines = load_data("something.txt");
	for (int i = 0; i < AssemCodeLines.size(); i++) {
		string label = validate(AssemCodeLines[i]);
		if (label.length() > 0) {
			AssemCodeLines.insert(AssemCodeLines.begin() + i, label);
		}
	}

	for (string line : AssemCodeLines) {
		cout << line << endl;
	}


	return 0;
}
