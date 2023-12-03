#include <iostream>

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <cassert>
#include <algorithm>

using namespace std;

enum class cell_type {
	sensor,
	beacon,
	no_beacon
};

using map_type = unordered_map<int, unordered_map<int, cell_type>>;

int xmin{ std::numeric_limits<int>::max() };
int xmax{ std::numeric_limits<int>::min() };
int ymin{ std::numeric_limits<int>::max() };
int ymax{ std::numeric_limits<int>::min() };

//constexpr int check_row = 10;
constexpr int check_row = 2000000;

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

	update_minmax(sensor_x - manhattan_distance, xmin, xmax);
	update_minmax(sensor_x + manhattan_distance, xmin, xmax);

	update_minmax(sensor_y - manhattan_distance, ymin, ymax);
	update_minmax(sensor_y + manhattan_distance, ymin, ymax);

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

	ifstream input("Day15.txt");

	map_type map;

	while (!input.eof()) {
		string line;
		getline(input, line);

		stringstream sline(line);

		int sensor_x, sensor_y, beacon_x, beacon_y;

		sline >> sensor_x >> sensor_y >> beacon_x >> beacon_y;

		map[sensor_y][sensor_x] = cell_type::sensor;
		map[beacon_y][beacon_x] = cell_type::beacon;

		update_minmax(sensor_x, xmin, xmax);
		update_minmax(beacon_x, xmin, xmax);

		update_minmax(sensor_y, ymin, ymax);
		update_minmax(beacon_y, ymin, ymax);

		//if (sensor_x == 8 && sensor_y == 7)
			update_area(map, sensor_x, sensor_y, beacon_x, beacon_y);

		printf("xmix %d, xmax %d, ymin %d, ymax %d\r", xmin, xmax, ymin, ymax);

	}

	input.close();

	printf("\n");

	//print_map(map, xmin, xmax, ymin, ymax);

	cout << "No beacons in row " << check_row << ": " << get_no_beacon_in_row(map, check_row) << endl;


	return 0;
}
