#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class list {
public:
	list(int number) : _number(number), _isNumber(true) {}
	list(vector<list> list) : _number(0), _isNumber(false), _subList(list) {}

private:
	bool _isNumber{ true };
	int _number{ 0 };
	vector<list> _subList;

	int compare(const list& other) {
		if (_isNumber && other._isNumber) {
			return _number == other._number ? 0 : _number < other._number ? -1 : 1;
		}
		else if (!_isNumber && !other._isNumber) {
			for (int i = 0; i < min(_subList.size(), other._subList.size()); ++i) {
				int comp = _subList[i].compare(other);
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
			list converted({ _number });
			return converted.compare(other);
		}
		else {
			list converted({ other._number });
			return compare(converted);
		}

	}
};


void test() {

}

int main() {
	cout << " AoC 2022 Day13" << endl;

	ifstream input("Day13test.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;
	}

	input.close();

	return 0;
}
