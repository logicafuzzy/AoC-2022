#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <typeinfo>
#include <sstream>
#include <stack>

using namespace std;

class list;
class list_leaf;
class value;

class list {
public:
	vector<list> l;

	virtual const list& get(int index) const { return l[index]; };
	virtual size_t size() const { return l.size();	};

	virtual bool operator <= (const list& other) const {
		if (typeid(*this) == typeid(value) && typeid(other) == typeid(value))
			return static_cast<const value*>(this)->v <= static_cast<const value&>(other).v;

		list left = *this;
		if (typeid(left) == typeid(value))
			left = list_leaf({static_cast<const value&>(left)});

		list right = other;
		if (typeid(right) == typeid(value))
			right = list_leaf({ static_cast<const value&>(right) });

		for (int i = 0; i < min(size(), other.size()); i++) {
			if (!(get(i) <= other.get(i)))
				return false;
		}
		//all less or equal until now, check size
		if (size() <= other.size())
			return true;
		
		return false;
	}
};

class list_leaf : public list {
public:
	list_leaf(vector<value> values_) : values(values_) {};

	vector<value> values;
	const list& get(int index) const override { return values[index]; };
	virtual size_t size() const override { return values.size(); }

};

class value : public list {
public:
	int v;
	const list& get(int index) const override { assert(false);  return *this; };
	virtual size_t size() const override { return 1; }
};

list make_list(const string& line) {
	list result;
	stack<list> context;

	for (char c : line) {

	}
}

void test() {

}

int main() {
	cout << " AoC 2022 Day13" << endl;

	ifstream input("Day13.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;
	}

	input.close();

	return 0;
}
