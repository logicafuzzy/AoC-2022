#include <iostream>

#include <fstream>
#include <string>
#include <iterator>
#include <sstream>

#include <unordered_map>

using namespace std;

enum class cell_type {
	air,
	rock,
	sand
};

int main() {
	cout << " AoC 2022 Day14" << endl;

	ifstream input("Day14test.txt");

	unordered_map<int, unordered_map<int, cell_type>> map;

	while (!input.eof()) {
		string line;
		getline(input, line);

		stringstream sline(line);

		int x1, y1;
		sline >> x1;
		sline >> y1;
		while (!sline.eof()) {
			int x2, y2;
			sline >> x2;
			sline >> y2;

		}
	}

	input.close();

	return 0;
}
