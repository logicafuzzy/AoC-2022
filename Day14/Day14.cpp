#include <iostream>

#include <fstream>
#include <string>
#include <iterator>
#include <sstream>

#include <unordered_map>
#include <cassert>

using namespace std;

enum class cell_type {
	air,
	rock,
	sand
};

enum class evolution_type {
	moving,
	rest,
	endless_void
};

using map_type = unordered_map<int, unordered_map<int, cell_type>>;

bool endless_void(map_type& map, int x, int y) {
	auto x_res = map.find(x);
	if (x_res == map.end()) {
		return true;
	}
	auto y_res = map[x].find(y);
	if (y_res == map[x].end()) {
		return true;
	}
	return false;
}

// return true if sand moved
evolution_type evolve(map_type& map, int& x, int& y) {
	if (endless_void(map, x, y +1 ))
		return evolution_type::endless_void;
	
	if (map[x][y + 1] == cell_type::air) {
		map[x][y + 1] = cell_type::sand;
		map[x][y] = cell_type::air;
		++y;
		return evolution_type::moving;
	}
	
	if (endless_void(map, x - 1, y + 1))
		return evolution_type::endless_void;
		
	if (map[x - 1][y + 1] == cell_type::air) {
		map[x - 1][y + 1] = cell_type::sand;
		map[x][y] = cell_type::air;
		--x; ++y;
		return evolution_type::moving;
	}

	if (endless_void(map, x + 1, y + 1))
		return evolution_type::endless_void;

	if (map[x + 1][y + 1] == cell_type::air) {
		map[x + 1][y + 1] = cell_type::sand;
		map[x][y] = cell_type::air;
		++x; ++y;
		return evolution_type::moving;
	}

	return evolution_type::rest;
}

void add_rock_line(map_type& map, int x1, int y1, int x2, int y2) {
	assert(x1 == x2 || y1 == y2);

	if (x1 == x2) {
		for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
			map[x1][y] = cell_type::rock;
		}
	}
	else {
		for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
			map[x][y1] = cell_type::rock;
		}
	}
}

void fill(map_type& map, int xmin, int xmax, int ymin, int ymax) {
	for (int x = xmin; x <= xmax; ++x) {
		for (int y = ymin; y <= ymax; ++y) {
			auto x_res = map.find(x);
			if (x_res == map.end() || map[x].find(y) == map[x].end()) {
				map[x][y] = cell_type::air;
			}
		}
	}
}

void print_map(map_type& map, int xmin, int xmax, int ymin, int ymax) {
	for (int y = ymin; y <= ymax; ++y) {
		for (int x = xmin; x <= xmax; ++x) {
			switch (map[x][y]) {
			case cell_type::air:
				cout << '.';
				break;
			case cell_type::rock:
				cout << '#';
				break;
			case cell_type::sand:
				cout << 'o';
				break;
			/*case cell_type::origin:
				cout << '+';
				break;
			case cell_type::endless_void:
				cout << '~';
				break;*/
			}
		}
		cout << endl;
	}
}

void update_minmax(int value, int& min, int& max) {
	if (value < min) {
		min = value;
	}
	if (value > max) {
		max = value;
	}
}

int main() {
	cout << " AoC 2022 Day14" << endl;

	ifstream input("Day14.txt");

	map_type map;

	int xorigin = 500;
	int yorigin = 0;

	map[xorigin][yorigin] = cell_type::air;

	int xmax = xorigin;
	int ymax = yorigin;
	int xmin = xmax;
	int ymin = ymax;

	while (!input.eof()) {
		string line;
		getline(input, line);

		stringstream sline(line);

		int x1, y1;
		sline >> x1;
		sline >> y1;

		update_minmax(x1, xmin, xmax);
		update_minmax(y1, ymin, ymax);

		while (!sline.eof()) {
			int x2, y2;
			sline >> x2;
			sline >> y2;
			add_rock_line(map, x1, y1, x2, y2);

			update_minmax(x2, xmin, xmax);
			update_minmax(y2, ymin, ymax);

			x1 = x2;
			y1 = y2;
		}
	}

	input.close();

	fill(map, xmin, xmax, ymin, ymax);

	print_map(map, xmin, xmax, ymin, ymax);

	int units = 0;
	while (true) {
		int x = xorigin;
		int y = yorigin;
		evolution_type evolution;
		do {
			evolution = evolve(map, x, y);
		} while (evolution == evolution_type::moving);

		if (evolution == evolution_type::endless_void) {
			break;
		}
		else {
			++units;
		}
	}

	print_map(map, xmin, xmax, ymin, ymax);

	cout << "Units: " << units << endl;

	return 0;
}
