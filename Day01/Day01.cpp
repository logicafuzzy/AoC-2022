#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


int main() {
	cout << " AoC 2022 Day 01" << endl;

	ifstream input("Day01.txt");

	string line;


	int index{ 0 };
	int max{ 0 };
	int current{ 0 };

	vector<int> rank{ 0,0,0 };
	//how many elements to keep track of, minus one
	constexpr int maxindex = 2;

	while (input) {
		getline(input, line);

		if (line.length() == 0) {
			if (max < current)
				max = current;

			if (current >= rank[maxindex])
			{
				rank.push_back(current);
				//sort from highest to lowest
				std::sort(rank.rbegin(), rank.rend());
				//remove smaller
				rank.pop_back();
			}

			cout << "index: " << index << " current: " << current << " max : " << max << endl;
			current = 0;
			index++;
		}
		else {
			current += stoi(line);
		}
	}

	cout << "current: " << current << endl;
	cout << "max of " << index << ": " << max << endl;

	cout << "sum of top " << maxindex + 1 << " elements: " << std::accumulate(rank.begin(), rank.end(), 0) << endl;

	input.close();

	return 0;
}
