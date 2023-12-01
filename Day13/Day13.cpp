#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <cassert>
#include <algorithm> 

#include "list.h"

using namespace std;

void make_lists(vector<list>& first, vector<list>& second);

void make_test_lists(vector<list>& first, vector<list>& second);

int main() {
	cout << " AoC 2022 Day13 " << endl;

	vector<bool> testResults{ true, true, false, true, false, true, false, false };
	constexpr bool isTest = false;

	int testIndex = 0;
	int count = 0;
	int index = 1;

	vector<list> first, second;
	vector<list> all;

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

	cout << "part 2: " << endl;

	all.reserve(first.size() * 2);

	all.insert(all.end(), first.begin(), first.end());
	all.insert(all.end(), second.begin(), second.end());

	vector<list> dividers{ {{2}}, {{6}} };

	all.insert(all.end(), dividers.begin(), dividers.end());

	std::sort(all.begin(), all.end());

	for (auto& list : all)
		cout << list.toString() << endl;


	auto it = std::find(all.begin(), all.end(), dividers[0]);
	assert(it != all.end());

	index = it - all.begin() + 1;

	cout << "first divider index: " << index << endl;

	it = std::find(all.begin(), all.end(), dividers[1]);
	assert(it != all.end());
	
	index *= it - all.begin() + 1;
	
	cout << "second divider index: " << it - all.begin() + 1 << endl;

	cout << "result: " << index << endl;

	return 0;
}
