#include <iostream>

#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <sstream>
#include <vector>

using namespace std;

set<pair<int, int>> visited{ {0, 0} };

vector<pair<int, int>> rope;

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

void add(pair<int, int>& head, const pair<int, int>& val) {
	head.first += val.first;
	head.second += val.second;
}

pair<int, int> diff(const pair<int, int>& A, const pair<int, int>& B) {
	return { A.first - B.first, A.second - B.second };
}

void moveEl(const pair<int, int>& ref, pair<int,int>& follower) {
	pair<int, int> dist = diff(ref, follower);

	if (abs(dist.first) == 2) {
		add(follower, { dist.first / 2, sgn(dist.second) });
		return;
	}

	if (abs(dist.second) == 2)
		add(follower, { sgn(dist.first), dist.second / 2 });
}

int main() {
	cout << " AoC 2022 Day09" << endl;

	ifstream input("Day09.txt");

	constexpr int ropesize = 10;

	rope.resize(ropesize, { 0,0 });

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		stringstream sline(line);
		string dir;
		getline(sline, dir, ' ');
		
		string arg;
		getline(sline, arg);

		int val = atoi(arg.data());

		pair<int, int> move;

		switch (dir[0]) {
		case 'R':
			move = { 1, 0 };
			break;
		case 'L':
			move = { -1, 0 };
			break;
		case 'U':
			move = { 0, -1 };
			break;
		case 'D':
			move = { 0, 1 };
			break;
		}

		for (int i = 0; i < val; i++) {
			add(rope.front(), move);

			for (int e = 1; e < rope.size(); e++)
				moveEl(rope[e-1], rope[e]);

			visited.insert(rope.back());

		}
	}

	input.close();

	cout << "Visited: " << visited.size() << endl;

	return 0;
}
