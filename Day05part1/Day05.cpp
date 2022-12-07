#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

using stacks = vector<stack<char>>;

stacks getStacks() {
	stacks result;

	ifstream input("Day05stacks.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		stack<char> s;

		for (auto& c : line)
			s.push(c);

		result.push_back(s);
	}

	return result;
}

string getTops(const stacks& s) {
	string result;

	for (const auto& r : s)
		if (!r.empty())
			result += r.top();

	return result;
}

void printStack(stack<char> s) {
	stack<char> temp;

	while (!s.empty()) {
		temp.push(s.top());
		s.pop();
	}

	while (!temp.empty()) {
		cout << temp.top();
		temp.pop();
	}
}

void printStacks(const stacks& s) {
	int i = 1;

	for (auto st : s) {
		cout << i++ << " ";

		printStack(st);

		cout << endl;
	}
}

string execCommands(stacks& s) {

	ifstream input("Day05.txt");

	while (input) {
		string line;
		getline(input, line);

		if (line.length() == 0)
			break;

		istringstream sline(line);

		string smove;
		getline(sline, smove, ' ');
		int move = atoi(smove.data());

		string sfrom;
		getline(sline, sfrom, ' ');
		int from = atoi(sfrom.data()) - 1;

		string sto;
		getline(sline, sto, ' ');
		int to = atoi(sto.data()) - 1;

		for (int i = 0; i < move; ++i)
		{
			s[to].push(s[from].top());
			s[from].pop();
			cout << getTops(s) << endl;
		}
	}

	return getTops(s);

}

int main() {
	cout << " AoC 2022 Day 05 part1" << endl;

	stacks stackinput = getStacks();

	cout << getTops(stackinput) << endl;
	printStacks(stackinput);
	printStacks(stackinput);

	cout << "Tops: " << execCommands(stackinput) << endl;

	return 0;

}
