#include <iostream>

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

int cycle = 0;
int X = 1;
int strength = 0;
vector<char> crt;

void updatecrt() {
	if (X >= (cycle - 1)%40 - 1 && X <= (cycle - 1)%40 + 1)
		crt.push_back('#');
	else
		crt.push_back('.');
}

void increment() {
	cycle++;

	if (cycle == 20 || (cycle > 20 && (cycle - 20) % 40 == 0)) {
		strength += cycle * X;
		cout << "cycle: " << cycle << " X: " << X << " strength: " << strength << endl;
	}

	updatecrt();
}

void rendercrt() {
	int i = 1;
	for (char c : crt) {
		cout << c;

		if (i % 40 == 0)
			cout << endl;

		i++;
	}
}

int main() {
	cout << " AoC 2022 Day10" << endl;

	ifstream input("Day10.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		istringstream sline(line);
		string cmd;
		getline(sline, cmd, ' ');

		if (cmd.compare("addx") == 0) {
			string sval;
			getline(sline, sval);

			int val = atoi(sval.data());
			increment();
			increment();
			X += val;
		}
		else
			increment();

	}

	rendercrt();

	input.close();

	return 0;
}
