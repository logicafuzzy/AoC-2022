#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <cassert>

#include "list.h"

using namespace std;

void make_lists(vector<list>& first, vector<list>& second);

void make_test_lists(vector<list>& first, vector<list>& second);

void test() {
	cout << " AoC 2022 Day13 test" << endl;

	ifstream input("Day13test.txt");

	vector<bool> testResults{ true, true, false, true, false, true, false, false };

	constexpr bool isTest = false;
	int testIndex = 0;
	int count = 0;
	int index = 1;

	//vector<list> first({ {1,1,3,1,1}, {{1},{2,3,4}}, {9} });
	//vector<list> second({ {1,1,5,1,1}, {{1}, 4}, {{8,7,6}} });

	vector<list> first, second;

	if (isTest)
		make_test_lists(first, second);
	else
		make_lists(first, second);

	assert(first.size() == second.size());

	for (int i = 0; i < first.size(); ++i) {

		bool result = first[i].compare(second[i]) == -1;

		count += result ? index : 0;

		if (isTest)
			cout << "result: " << std::boolalpha << result << " passed: " << (result == testResults[testIndex++]) << endl;

		index++;
	}

	cout << "right order index sum: " << count << endl;
	input.close();
}

int main() {
	cout << " AoC 2022 Day13 test" << endl;

	test();

	return 0;
	ifstream input("Day13.txt");

	vector<bool> testResults{ true, true, false, true, false, true, false, false };

	constexpr bool isTest = true;
	int testIndex = 0;
	int count = 0;
	int index = 1;

	vector<list> first{ {1,1,3,1,1}, {{1},{2,3,4}} };
	vector<list> second({ {1,1,5,1,1} });

	while (input) {
		string line1, line2, ignore;
		getline(input, line1);
		getline(input, line2);
		getline(input, ignore);

		cout << line1 << endl;
		cout << line2 << endl;

		bool result = line1.compare(line2) == -1;
		
		count += result ? index : 0;

		if (isTest)
			cout << "result: " << (result == testResults[testIndex++]) << endl;

		cout << "right order index sum: " << count;

		index++;

	}

	input.close();

	return 0;
}
