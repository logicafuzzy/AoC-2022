#pragma once

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class list {
public:
	list(int number) : _number(number), _isNumber(true) {}
	list(std::initializer_list<list> list) : _number(0), _isNumber(false), _subList(list) {}

	int compare(const list& other) {
		if (_isNumber && other._isNumber) {
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
			list converted{ _number };
			return converted.compare(other);
		}
		else {
			list converted{ other._number };
			return compare(converted);
		}

	}

	bool operator<(const list& other) {
		return compare(other) == -1;
	}

	bool operator==(const list& other) {
		return compare(other) == 0;
	}

	string toString() {
		stringstream s;

		if (_isNumber)
			s << _number;
		else {
			s << "[";
			for (auto& list : _subList)
				s << list.toString() << " ";
			s << "]";
		}

		return s.str();
	}

private:
	bool _isNumber{ true };
	int _number{ 0 };
	std::vector<list> _subList;
};