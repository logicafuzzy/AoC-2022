#include <iostream>

#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> start;
pair<int, int> goal;

vector<vector<int>> map;

struct path {
	int row = 0;
	int col = 0;
	vector<pair<int, int>> prev;
	bool finish = false;
	bool dead = false;
};

vector<path> solutions;


vector<vector<int>> getMap() {
	vector<vector<int>> result;

	ifstream input("Day12.txt");

	int row = 0;
	int col = 0;

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		vector<int> maprow;
		col = 0;
		for (auto c : line) {
			if (c == 'S') {
				c = 'a';
				start = { row, col };
			}
			else if (c == 'E') {
				c = 'z';
				goal = { row, col };
			}

			if (c >= 'a' && c <= 'z')
				maprow.push_back(c - 97);

			col++;
		}
		
		result.push_back(maprow);

		row++;
	}

	input.close();

	return result;
}

bool hasPrev(const path& pos, int row, int col) {
	for (const auto& p : pos.prev)
		if (p.first == row && p.second == col)
			return true;

	return false;
}

vector<path> getBranches(const path& pos) {
	int curr = map[pos.row][pos.col];

	path eval;

	vector<path> results;

    // /*
	//  01234567
	// 0v..v<<<<
	// 1>v.vv<<^
	// 2.>vv>E^^
	// 3..v>>>^^
	// 4..>>>>>^
	// */

	// if (hasPrev(pos, 0, 0) 
	// && hasPrev(pos, 1, 0) 
	// && hasPrev(pos, 1, 1) 
	// && hasPrev(pos, 2, 1) 
	// && hasPrev(pos, 2, 2) 
	// && hasPrev(pos, 3, 2) 
	// && hasPrev(pos, 4, 2) 
	// && hasPrev(pos, 4, 3) 
	// && hasPrev(pos, 4, 4) 
	// && hasPrev(pos, 4, 5) 
	// && hasPrev(pos, 4, 6) 
	// && hasPrev(pos, 4, 7) 
	// && hasPrev(pos, 3, 7) 
	// && hasPrev(pos, 2, 7) 
	// && hasPrev(pos, 1, 7) 
	// && hasPrev(pos, 0, 7) 
	// && hasPrev(pos, 0, 6) 
	// && hasPrev(pos, 0, 5) 
	// && hasPrev(pos, 0, 4) 
	// && hasPrev(pos, 0, 3) 
	// && hasPrev(pos, 1, 3) 
	// && hasPrev(pos, 2, 3) 
	// && hasPrev(pos, 3, 3) 
	// && hasPrev(pos, 3, 4) 
	// && hasPrev(pos, 3, 5) 
	// && hasPrev(pos, 3, 6) 
	// && hasPrev(pos, 2, 6) 
	// && hasPrev(pos, 1, 6)
	// && hasPrev(pos, 1, 5)
	// && hasPrev(pos, 1, 4)
	// && (pos.row == 2 && pos.col == 4))
	// 	cout << "test" << endl;

	for (int r = pos.row - 1; r <= pos.row + 1; r++) {
		for (int c = pos.col - 1; c <= pos.col + 1; c++) {
			if (r >= 0 && r < map.size() // valid row
				&& c >= 0 && c < map[r].size() // valid col
				&& !(r == pos.row && c == pos.col) // not current pos (to eval)
				&& ( r == pos.row || c == pos.col) // not diagonal
				&& !hasPrev(pos, r, c) // not loop
				&& map[r][c] <= curr + 1) { // at most one higher
				results.push_back({ r, c, pos.prev });
			}
		}
	}

	for (auto& r : results) {
		if (r.row == goal.first && r.col == goal.second)
			r.finish = true;

		r.prev.push_back({ pos.row, pos.col });
	}

	return results;
}

int getMinSolution(const vector<path>& solution) {
	int minSteps = 100000;
	for (auto& s : solution)
	{
		if (s.finish && s.prev.size() < minSteps)
			minSteps = s.prev.size();
	}
	return minSteps;
}

void printPath(const path& p) {
	int i = 48;

	vector<vector<char>> newmap;
	vector<char> col;
	col.resize(map[0].size(), '.');
	newmap.resize(map.size(), col);

	for (const auto& prev : p.prev) {
		newmap[prev.first][prev.second] = i++;
	}

	for (int r = 0; r < map.size(); r++) {
		for (int c = 0; c < map[r].size(); c++) {
			cout << newmap[r][c];
		}
		cout << endl;
	}
}

int main() {
	cout << " AoC 2022 Day12" << endl;

	map = getMap();

	solutions.push_back({ start.first, start.second });

	while (true) {
		vector<path> newsolutions;
		for (auto& s : solutions) {
			auto branches = getBranches(s);
			if (branches.size() > 0)
				newsolutions.insert(newsolutions.end(), branches.begin(), branches.end());
			else
				s.dead = true;
		}

		solutions = newsolutions;

		int minSteps = getMinSolution(solutions);

		solutions.erase(remove_if(solutions.begin(), solutions.end(), [minSteps](const path& el) { return el.dead || (!el.finish && el.prev.size() >= minSteps); }), solutions.end());

		bool allFinish = true;
		for (const auto& s : solutions)
			allFinish = allFinish && s.finish;

		if (allFinish)
			break;

	}

	cout << "Minsteps: " << getMinSolution(solutions) << endl;

	for (const auto& s : solutions) {
		printPath(s);
		cout << endl;
	}

	return 0;
}
