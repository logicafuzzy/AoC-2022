#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

bool isVisible(const vector<vector<int>>& forest, int i, int j) {
	int rows = forest.size();
	
	assert(rows > 0);

	int cols = forest[0].size();

	//if edges, return true
	if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
		return true;

	const int ref = forest[i][j];

	bool v = true;
	//go right
	for (int c = j + 1; c < cols; c++) {
		if (forest[i][c] >= ref)
		{
			v = false;
			break;
		}
	}

	if (v == true)
		return true;

	//go left
	v = true;
	for (int c = j - 1; c >= 0; c--) {
		if (forest[i][c] >= ref)
		{
			v = false;
			break;
		}
	}

	if (v == true)
		return true;

	//go down
	v = true;
	for (int r = i + 1; r < rows; r++) {
		if (forest[r][j] >= ref)
		{
			v = false;
			break;
		}
	}

	if (v == true)
		return true;

	//go up
	v = true;
	for (int r = i - 1; r >= 0; r--) {
		if (forest[r][j] >= ref)
		{
			v = false;
			break;
		}
	}

	return v;
}

int score(const vector<vector<int>>& forest, int i, int j) {
	int rows = forest.size();

	assert(rows > 0);

	int cols = forest[0].size();

	//if edges, return true
	if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
		return 0;

	const int ref = forest[i][j];

	int rVisible = 0;
	//go right
	for (int c = j + 1; c < cols; c++) {
		//if (forest[i][c] <= ref)
			rVisible++;
		
		if (forest[i][c] >= ref)
			break;
	}

	//go left
	int lVisible = 0;
	for (int c = j - 1; c >= 0; c--) {
		//if (forest[i][c] <= ref)
			lVisible++;

		if (forest[i][c] >= ref)
			break;
	}

	//go down
	int dVisible = 0;
	for (int r = i + 1; r < rows; r++) {
		//if (forest[r][j] <= ref)
			dVisible++;

		if (forest[r][j] >= ref)
			break;
	}

	//go up
	int uVisible = 0;
	for (int r = i - 1; r >= 0; r--) {
		//if (forest[r][j] <= ref)
			uVisible++;
		
		if (forest[r][j] >= ref)
			break;
	}

	return rVisible * lVisible * dVisible * uVisible;
}

int main() {
	cout << " AoC 2022 Day08" << endl;

	ifstream input("Day08.txt");

	vector<vector<int>> forest;

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		vector<int> treeline;
		for (auto& c : line)
			treeline.push_back(c - 48);

		forest.push_back(treeline);
	}

	int visible = 0;
	int max_score = 0;

	for (int i = 0; i < forest.size(); i++)
		for (int j = 0; j < forest[i].size(); j++) {
			visible += isVisible(forest, i, j) ? 1 : 0;
			int treescore = score(forest, i, j);
			max_score = max(max_score, treescore);
		}

	input.close();

	cout << "Visible: " << visible << endl;
	cout << "Score: " << max_score << endl;
	return 0;
}
