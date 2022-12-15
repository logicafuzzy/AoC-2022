#include <iostream>

#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

pair<int, int> start;
pair<int, int> goal;

vector<vector<int>> mapmatrix;
map<pair<int, int>, size_t> visited;

struct path {
	int row = 0;
	int col = 0;
	vector<pair<int, int>> prev;
	bool finish = false;
	bool dead = false;
};

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
				maprow.push_back(c );

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
	int curr = mapmatrix[pos.row][pos.col];

	path eval;

	vector<path> results;

	for (int r = pos.row - 1; r <= pos.row + 1; r++) {
		for (int c = pos.col - 1; c <= pos.col + 1; c++) {
			if (r >= 0 && r < mapmatrix.size() // valid row
				&& c >= 0 && c < mapmatrix[r].size() // valid col
				&& !(r == pos.row && c == pos.col) // not current pos (to eval)
				&& (r == pos.row || c == pos.col) // not diagonal
				&& !hasPrev(pos, r, c) // not loop
				&& mapmatrix[r][c] <= curr + 1 // at most one higher
				&& (visited.find({ r, c }) == visited.end() || visited.find({ r, c })->second < pos.prev.size()) //not visited with better results
				) {
				results.push_back({ r, c, pos.prev });
				visited[{ r, c }] = pos.prev.size();
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
	int minSteps = 10000;
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
	col.resize(mapmatrix[0].size(), '.');
	newmap.resize(mapmatrix.size(), col);

	for (const auto& prev : p.prev) {
		newmap[prev.first][prev.second] = i++;
	}

	for (int r = 0; r < mapmatrix.size(); r++) {
		for (int c = 0; c < mapmatrix[r].size(); c++) {
			cout << newmap[r][c];
		}
		cout << endl;
	}
}

int getMinPath(int startrow, int startcol) {
	vector<path> solutions;

	visited.clear();

	solutions.push_back({startrow, startcol});

	while (true) {
		vector<path> newsolutions;
		for (auto& s : solutions) {
			auto branches = getBranches(s);
			if (branches.size() > 0)
				newsolutions.insert(newsolutions.end(), branches.begin(), branches.end());
			else
				s.dead = true;
		}

		solutions = move(newsolutions);

		int minSteps = getMinSolution(solutions);

		solutions.erase(remove_if(solutions.begin(), solutions.end(), [minSteps](const path& el) {
			return el.dead || (!el.finish && el.prev.size() >= minSteps) || (visited.find({ el.row, el.col }) != visited.end() && visited.find({ el.row, el.col })->second > el.prev.size()); }), solutions.end());

		bool allFinish = true;
		for (const auto& s : solutions)
			allFinish = allFinish && s.finish;

		if (allFinish)
			break;

	}

	int minPath = getMinSolution(solutions);

	cout << "Minsteps: " << minPath << endl;

	return minPath;
}

int main() {
	cout << " AoC 2022 Day12" << endl;

	mapmatrix = getMap();

	int minPath = 10000;
	
	int row = 0;
	int col = 0;

	for (int r = 0; r < mapmatrix.size(); r++) {
		for (int c = 0; c < mapmatrix[r].size(); c++) {
			if (mapmatrix[r][c] == 'a') {
				int tempmin = getMinPath(r, c);

				if (tempmin < minPath)
					minPath = tempmin;
			}
		}
	}

	cout << "Minpath starting from an a: " << minPath << endl;
	//for (const auto& s : solutions) {
	//	printPath(s);
	//	cout << endl;
	//}

	return 0;
}
