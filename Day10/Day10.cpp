#include <iostream>

#include <fstream>
#include <string>

using namespace std;

int main() {
	cout << " AoC 2022 Day10" << endl;

	ifstream input("Day10.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;
	}

	input.close();

	return 0;
}
