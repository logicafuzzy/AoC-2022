#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
//for pair
#include <utility>

using namespace std;

int getPriority(char c) {
    if (c >= 97)
        return c - 96;
    
    return c - 38;
};

bool test() {
    assert(getPriority('a') == 1);
    assert(getPriority('A') == 27);
    assert(getPriority('p') == 16);
    assert(getPriority('L') == 38);
    assert(getPriority('P') == 42);
    assert(getPriority('v') == 22);
    assert(getPriority('t') == 20);
    assert(getPriority('s') == 19);

    return true;
};

set<char> toCharSet(string s) {
    set<char> result;
    for(auto& c : s)
        result.insert(c);

    //assert(s.length() == result.size());

    return result;
}

char getRepeated(string left, string right) {
    assert(left.length() == right.length());

    std::set<char> lset = toCharSet(left);
    std::set<char> rset = toCharSet(right);

    std::vector<char> intersection;

    std::set_intersection(lset.begin(), lset.end(),
        rset.begin(), rset.end(),
        std::back_inserter(intersection));

    assert(intersection.size() == 1);

    return intersection[0];
}

pair<string, string> getHalves(string s) {
    //must have even size
    assert(s.length() % 2 == 0);

    int halfsize = s.length() / 2;

    pair<string,string> result;

    result.first = s.substr(0, halfsize);
    result.second = s.substr(halfsize, s.length() - 1);

    assert(result.first.length() == result.second.length());

    return result;
}

int main() {
	cout << " AoC 2022 Day 03 part1" << endl;

    test();

    ifstream input("Day03.txt");

    int points = 0;

    while (input) {
        string line;
        getline(input, line);

        if (line.length() == 0)
            break;

        cout << "Element: " << line << endl;

        pair<string, string> halves = getHalves(line);

        cout << "Halves: " << halves.first << " " << halves.second << endl;

        char c = getRepeated(halves.first, halves.second);
        int priority = getPriority(c);

        cout << "Repeated: " << c << "(" << priority << ")" << endl;

        points += priority;
    }

    cout << "Total points: " << points << endl;

    return 0;
}