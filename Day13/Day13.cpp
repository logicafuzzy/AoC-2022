#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <cassert>

using namespace std;

class list {
public:
	list(int number) : _number(number), _isNumber(true) {}
	list(std::initializer_list<list> list) : _number(0), _isNumber(false), _subList(list) {}

	int compare(const list& other) {
		if (_isNumber && other._isNumber) {
			cout << "compare " << _number << " with " << other._number << endl;
			return _number == other._number ? 0 : _number < other._number ? -1 : 1;
		}
		else if (!_isNumber && !other._isNumber) {
			for (int i = 0; i < min(_subList.size(), other._subList.size()); ++i) {
				int comp = _subList[i].compare(other._subList[i]);
				if (comp == 0)
					continue;
				else
					return comp;
			}

			if (_subList.size() == other._subList.size())
				return 0;
			else
				return _subList.size() > other._subList.size() ? 1 : -1;
		}
		else if (_isNumber) {
			list converted{ {_number} };
			return converted.compare(other);
		}
		else {
			list converted{ {other._number} };
			return compare(converted);
		}

	}
private:
	bool _isNumber{ true };
	int _number{ 0 };
	std::vector<list> _subList;
};

//list make_list(std::string string) {
//	
//}

void test() {
	cout << " AoC 2022 Day13 test" << endl;

	ifstream input("Day13test.txt");

	vector<bool> testResults{ true, true, false, true, false, true, false, false };

	constexpr bool isTest = true;
	int testIndex = 0;
	int count = 0;
	int index = 1;

	vector<list> first({ {1,1,3,1,1}, {{{1}},{2,3,4}}, {{9}} });
	vector<list> second({ {1,1,5,1,1}, {{{1}}, 4}, {{8,7,6}} });

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
