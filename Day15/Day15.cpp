#include <iostream>

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <cassert>
#include <algorithm>

using namespace std;

enum class cell_type {
	sensor,
	beacon,
	no_beacon,
	no_beacon_right,
	no_beacon_left,
	no_beacon_up,
	no_beacon_down
};

using map_type = map<int, map<int, cell_type>>;

int xmin{ std::numeric_limits<int>::max() };
int xmax{ std::numeric_limits<int>::min() };
int ymin{ std::numeric_limits<int>::max() };
int ymax{ std::numeric_limits<int>::min() };

#define TEST
#define PART2

#ifdef TEST
constexpr int check_row = 10;
constexpr int max_coord = 20;
#else
constexpr int check_row = 2000000;
constexpr int max_coord = 4000000;
#endif

void print_map(map_type& map, int xmin, int xmax, int ymin, int ymax) {
	for (int y = ymin; y <= ymax; ++y) {
		for (int x = xmin; x <= xmax; ++x) {
			if (map.find(y) != map.end() && map[y].find(x) != map[y].end()) {
				switch (map[y][x]) {
				case cell_type::sensor:
					cout << 'S';
					break;
				case cell_type::beacon:
					cout << 'B';
					break;
				case cell_type::no_beacon:
					cout << '#';
					break;
				case cell_type::no_beacon_right:
					cout << '>';
					break;
				case cell_type::no_beacon_left:
					cout << '<';
					break;
				case cell_type::no_beacon_up:
					cout << '^';
					break;
				case cell_type::no_beacon_down:
					cout << 'v';
					break;
				}
			}
			else {
				cout << '.';
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

#ifdef PART2
void add_line(map_type& map, int x1, int y1, int x2, int y2) {
	assert(x1 == x2 || y1 == y2);

	if (x1 == x2) {
		
		if (y2 < y1) 
			swap(y1, y2);

		y1 = max(y1, 0);
		y2 = min(y2, max_coord);

		if (y1 < max_coord && y2 >= 0) {
			map[y1][x1] = cell_type::no_beacon_down;
			map[y2][x1] = cell_type::no_beacon_up;
		}
	}
	else {
		if (y1 < 0 || y1 > max_coord)
			return;

		if (x2 < x1)
			swap(x1, x2);

		x1 = max(x1, 0);
		x2 = min(x2, max_coord);

		if (x1 < max_coord && x2 > 0) {
			map[y1][x1] = cell_type::no_beacon_right;
			map[y1][x2] = cell_type::no_beacon_left;
		}
	}
}
#else
void add_line(map_type& map, int x1, int y1, int x2, int y2) {
	assert(x1 == x2 || y1 == y2);

	if (x1 == x2) {
		if (min(y1, y2) <= check_row && max(y1, y2) >= check_row &&
			(map.find(check_row) == map.end() || map[check_row].find(x1) == map[check_row].end()))
			map[check_row][x1] = cell_type::no_beacon;
	}
	else {
		if (y1 != check_row)
			return;
		for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
			if (map.find(y1) == map.end() || map[y1].find(x) == map[y1].end())
				map[y1][x] = cell_type::no_beacon;
		}
	}
}
#endif

void update_area(map_type& map, int sensor_x, int sensor_y, int beacon_x, int beacon_y) {
	int manhattan_distance = abs(beacon_x - sensor_x) + abs(beacon_y - sensor_y);
	// todo update min and max
	for (int i = 0; i <= manhattan_distance; ++i) {
		// down right
		add_line(map, sensor_x + i, sensor_y, sensor_x + i, sensor_y + manhattan_distance - i);
		// up right
		add_line(map, sensor_x + i, sensor_y, sensor_x + i, sensor_y - manhattan_distance + i);

		//down left
		add_line(map, sensor_x, sensor_y + i, sensor_x - manhattan_distance + i, sensor_y + i);
		//up left
		add_line(map, sensor_x, sensor_y - i, sensor_x - manhattan_distance + i, sensor_y - i);
	}

#ifdef TEST
	update_minmax(sensor_x - manhattan_distance, xmin, xmax);
	update_minmax(sensor_x + manhattan_distance, xmin, xmax);

	update_minmax(sensor_y - manhattan_distance, ymin, ymax);
	update_minmax(sensor_y + manhattan_distance, ymin, ymax);
#endif
}

int get_no_beacon_in_row(map_type& map, int y) {
	int result = 0;
	for (auto& row : map[y]) {
		result += row.second == cell_type::no_beacon ? 1 : 0;
	}
	return result;
}

int main() {
	cout << " AoC 2022 Day15" << endl;

#ifdef TEST
	ifstream input("Day15test.txt");
#else
	ifstream input("Day15.txt");
#endif

	map_type map;

	while (!input.eof()) {
		string line;
		getline(input, line);

		stringstream sline(line);

		int sensor_x, sensor_y, beacon_x, beacon_y;

		sline >> sensor_x >> sensor_y >> beacon_x >> beacon_y;

		map[sensor_y][sensor_x] = cell_type::sensor;
		map[beacon_y][beacon_x] = cell_type::beacon;

#ifdef TEST
		update_minmax(sensor_x, xmin, xmax);
		update_minmax(beacon_x, xmin, xmax);

		update_minmax(sensor_y, ymin, ymax);
		update_minmax(beacon_y, ymin, ymax);
#endif

		if (sensor_x == 8 && sensor_y == 7)
			update_area(map, sensor_x, sensor_y, beacon_x, beacon_y);

		printf("xmix %d, xmax %d, ymin %d, ymax %d\r", xmin, xmax, ymin, ymax);

	}

	input.close();

	printf("\n");

#ifdef TEST
	#ifdef PART2
		print_map(map, 0, max_coord, 0, max_coord);
	#else
		print_map(map, xmin, xmax, ymin, ymax);
	#endif
#endif
	
#ifdef PART2
	int beacon_x, beacon_y;

	//find row with only one empty
	for (auto& row : map) {
		beacon_y = row.first;
		if (beacon_y < 0 || beacon_y > max_coord)
			continue;
		int count = 0;
		int cell_xmin = max_coord;
		int cell_xmax = 0;
		for (auto& cell : row.second) {
			beacon_x = cell.first;
			if (beacon_x < 0 || beacon_x > max_coord)
				continue;
			update_minmax(beacon_x, cell_xmin, cell_xmax);
			++count;
		}
		printf("Row %d count: %d\n", beacon_y, count);
		if (count == cell_xmax - cell_xmin)
			break;
	}
	for (int i = 0; i <= max_coord; ++i) {
		auto& row = map[beacon_y];
		if (row.find(i) == row.end()) {
			beacon_x = i;
			break;
		}
	}
	printf("Beacon in %d, %d frequency: %d", beacon_x, beacon_y, beacon_x * 4000000 + beacon_y);
#else
	cout << "No beacons in row " << check_row << ": " << get_no_beacon_in_row(map, check_row) << endl;
#endif

	return 0;
}
