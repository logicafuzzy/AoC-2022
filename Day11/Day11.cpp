#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>

#include "BigInt.hpp"

using namespace std;

struct monkey {
	vector<BigInt> items;
	bool square = false;
	int mult = 0;
	int add = 0;
	int testdiv = 0;
	int throwtrue = 0;
	int throwfalse = 0;
	int inspectcount = 0;
};


void populate_test(vector<monkey>& monkeys) {
	monkeys.push_back({ {79,98},			false, 19, 0, 23, 2, 3 });
	monkeys.push_back({ {54, 65, 75, 74},	false, 1,  6, 19, 2, 0 });
	monkeys.push_back({ {79, 60, 97},		true , 0,  0, 13, 1, 3 });
	monkeys.push_back({ {74},				false, 1,  3, 17, 0, 1 });
}

void populate_input(vector<monkey>& monkeys) {
	monkeys.push_back({ {98, 97, 98, 55, 56, 72},			false, 13, 0, 11, 4, 7 });
	monkeys.push_back({ {73, 99, 55, 54, 88, 50, 55},		false,  1, 4, 17, 2, 6 });
	monkeys.push_back({ {67, 98},							false, 11, 0,  5, 6, 5 });
	monkeys.push_back({ {82, 91, 92, 53, 99},				false,  1, 8, 13, 1, 2 });
	monkeys.push_back({ {52, 62, 94, 96, 52, 87, 53, 60},	true ,  0, 0, 19, 3, 1 });
	monkeys.push_back({ {94, 80, 84, 79},					false,  1, 5,  2, 7, 0 });
	monkeys.push_back({ {89},								false,  1, 1,  3, 0, 5 });
	monkeys.push_back({ {70, 59, 63},						false,  1, 3,  7, 4, 3 });


}

int main() {
	cout << " AoC 2022 Day11" << endl;

	vector<monkey> monkeys;

	populate_input(monkeys);

	long divmax = 1;
	for (auto& m : monkeys)
		if (m.testdiv > 1)
			divmax *= m.testdiv;

	for (int round = 0; round < 10000; round++) {
		cout << "Round: " << round << endl;
		for (auto& monkey : monkeys) {
			for (auto item : monkey.items) {
				item = monkey.square ? item * item : 0 + item * monkey.mult + monkey.add;

				auto val = item%divmax;
				item = val == 0 ? divmax : val;

				if (item % monkey.testdiv == 0) {
					monkeys[monkey.throwtrue].items.push_back(item);
				} 
				else {
					monkeys[monkey.throwfalse].items.push_back(item);
				}

				monkey.inspectcount++;
			}
			 
			monkey.items = {};
		}

		//int m = 0;
		//for (const auto& monkey : monkeys) {
		//	cout << "Monkey " << m++ << ": ";

		//	for (auto& item : monkey.items)
		//		cout << item << " ";
		//	
		//	cout << endl;
		//}
	}

	int i = 0;
	vector<BigInt> inspectcount;
	for (const auto& monkey : monkeys) {
		cout << "Monkey " << i++ << " inspected items " << monkey.inspectcount << " times." << endl;
		inspectcount.push_back(monkey.inspectcount);
	}

	sort(inspectcount.begin(), inspectcount.end(), [](auto a, auto b) {return a > b; });

	cout << "Result: " << inspectcount[0] << " * " << inspectcount[1] << " = " << inspectcount[0] * inspectcount[1] << endl;

	return 0;
}
