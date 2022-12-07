#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <set>
#include <cassert>

using namespace std;

int getStartOfPacketIndex(string s, int size) {
	deque<char> window;

	int index = 0;

	for (auto& c : s) {
		window.push_back(c);
		
		index++;
		
		if (window.size() > size) {
			window.pop_front();

		set<char> charset;
		for (auto& k : window) {
			charset.insert(k);
		}
		if (charset.size() == size)
			return index;
		}
	}
	return 0;
}

void test() {
	assert(getStartOfPacketIndex("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 4) == 7);
	assert(getStartOfPacketIndex("bvwbjplbgvbhsrlpgdmjqwftvncz", 4) == 5);
	assert(getStartOfPacketIndex("nppdvjthqldpwncqszvftbrmjlhg", 4) == 6);
	assert(getStartOfPacketIndex("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 4) == 10);
	assert(getStartOfPacketIndex("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 4) == 11);

	assert(getStartOfPacketIndex("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 14) == 19);
	assert(getStartOfPacketIndex("bvwbjplbgvbhsrlpgdmjqwftvncz", 14) == 23);
	assert(getStartOfPacketIndex("nppdvjthqldpwncqszvftbrmjlhg", 14) == 23);
	assert(getStartOfPacketIndex("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 14) == 29);
	assert(getStartOfPacketIndex("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 14) == 26);
}

int main() {
	cout << " AoC 2022 Day 06 part1" << endl;

	test();

	ifstream input("Day06part1.txt");

	string line;
	getline(input, line);

	cout << "start-of-packet: " << getStartOfPacketIndex(line, 4) << endl;
	cout << "start-of-packet: " << getStartOfPacketIndex(line, 14) << endl;
	return 0;

}

