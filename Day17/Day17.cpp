#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "rock.hpp"


using namespace std;

struct pattern {
	int rock_id;
	int jet_id;
	unsigned long extent;
};

unsigned long get_free_rows(const rock_t::chamber_t& chamber) {
	for (unsigned long i = 0; i < chamber.size(); i++)
		for(const auto& c : chamber[i])
			if (c)
				return i;

	return chamber.size();
}

unsigned long get_reachable_row(const rock_t::chamber_t& chamber) {
	bitset<rock_t::area_width> stop, test;
	stop.reset(); //all 0
	test.set();   //all 1

	for (unsigned long i = 0; i < chamber.size(); i++) {
		for (int c = 0; c < chamber[i].size(); c++) {
			if (!stop[c] && chamber[i][c])
				stop.set(c);
		}
		if (stop == test)
			return i;
		
	}		

	return chamber.size();
}

void add_rows(rock_t::chamber_t& chamber, unsigned long count) {
	rock_t::chamber_row_t row;

	row.fill(false);

	vector<decltype(row)> rows;
	rows.resize(count, row);

	chamber.insert(chamber.begin(), rows.begin(), rows.end());
}

unsigned long get_jet_dir(char c) {
	return c == '>' ? 1 : c == '<' ? -1 : 0;
}

void print_chamber(const rock_t::chamber_t& chamber) {
	for (auto& row : chamber) {
		for (int i = 0; i < row.size(); i++) {
			cout << (row[i] ? '#' : '.') << ' ';
		}
		cout << endl;
	}

	cout << endl;
}

void print_chamber(rock_t::chamber_t chamber, const rock_t& rock, unsigned long left_offset, unsigned long top_offset) {
	rock.set_position(chamber, left_offset, top_offset);

	print_chamber(chamber);
}

int main() {
	cout << " AoC 2022 Day17" << endl;

	rock_t::chamber_t chamber;

	ifstream input("Day17test.txt");

	string line;
	getline(input, line);
	input.close();

	vector<char> jets;
	copy(line.begin(), line.end(), back_inserter(jets));

	//const unsigned long long n_rocks = 2022;
	//const unsigned long long n_rocks =   1000000000;
	const unsigned long long n_rocks = 1000000000000ul;

	unsigned long long stopped_rocks = 0;

	rock_t rock0({ {1, 1, 1, 1} });

	rock_t rock1({ {0, 1, 0},
					{1, 1, 1},
					{0, 1, 0} });

	rock_t rock2({	{0, 0, 1},
					{0, 0, 1},
					{1, 1, 1} });

	rock_t rock3({ {1},
					{1},
					{1},
					{1} });

	rock_t rock4({  {1, 1},
					{1, 1} });

	vector<rock_t> rocks = { rock0, rock1, rock2, rock3, rock4};
	int rock_index = 0;
	int jet_index = 0;
	unsigned long deleted = 0;
	long latest_top = 0;

	while (stopped_rocks < n_rocks) {
		const rock_t& rock = rocks[rock_index];
		
		if (stopped_rocks % 100 == 0) {
			unsigned long reachable = get_reachable_row(chamber);

			if (reachable < chamber.size()) {
				deleted += chamber.size() - reachable;
				chamber.erase(chamber.begin() + reachable, chamber.end());
			}
		}

		// don't call get_free_rows since is expensive but keep track of where lates rock went
		long free_rows = latest_top - 3 - rock.get_height(); //
		//long free_rows = get_free_rows(chamber) - 3 - rock.get_height();

		assert(free_rows == get_free_rows(chamber) - 3 - rock.get_height());

		if (free_rows < 0) {
			long new_rows = max(100l, -free_rows);
			add_rows(chamber, new_rows);
			latest_top += new_rows;
			free_rows = latest_top - 3 - rock.get_height();
		}

		int left_offset = 2;
		long top_offset = 0 + (free_rows > 0) ? free_rows : 0;

		while (rock.try_position(chamber, left_offset, top_offset)) {

			//print_chamber(chamber, rock, left_offset, top_offset);

			if (top_offset + rock.get_height() <= chamber.size()) { //not hit bottom, jet applies
				int jet_dir = get_jet_dir(jets[jet_index]);
				jet_index = ++jet_index % jets.size();

				if (rock.try_position(chamber, left_offset + jet_dir, top_offset))
					left_offset += jet_dir;

				//print_chamber(chamber, rock, left_offset, top_offset);
			}
			else {
				top_offset++;
				break;
			}

			top_offset++;
		}
		top_offset--;

		rock.set_position(chamber, left_offset, top_offset); //rock stopped

		latest_top = min(latest_top, top_offset);
		//print_chamber(chamber);

		rock_index = ++rock_index % rocks.size();
		stopped_rocks++;

		if (stopped_rocks % 1000000 == 0)
			cout << "cycle: " << stopped_rocks << " " << float(int((float)stopped_rocks / (float)n_rocks * 10000)) / 100.0 << "%" <<  endl;
	}

	//print_chamber(chamber);

	cout << "Tower height after " << n_rocks << " rocks: " << chamber.size() - get_free_rows(chamber) + deleted << endl;

	return 0;
}
