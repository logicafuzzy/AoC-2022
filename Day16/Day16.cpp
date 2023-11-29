#include <iostream>

#include <fstream>
#include <string>
#include <regex>
#include <iterator>

using namespace std;

int main() {
	cout << " AoC 2022 Day16" << endl;

	ifstream input("Day16test.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		regex line_regex("Valve (..) has flow rate=(\d+); tunnels? leads? to valves? (?:(..), )?(?:(..), )?(?:(..), )?(?:(..), )?(?:(..), )?(..)", regex_constants::match_any);

		auto match_begin = sregex_iterator(line.begin(), line.end(), line_regex);
		auto match_end = sregex_iterator();

		int nmatch = 0;
		for (sregex_iterator i = match_begin; i != match_end; ++i) {
			auto match = *i;
			string match_str = match.str();
			cout << "group" << nmatch++ << ": " << match_str << endl;
		}
	}

	input.close();

	return 0;
}
