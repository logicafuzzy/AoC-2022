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

    return result;
}

char getRepeated(string first, string second, string third) {
    std::set<char> set1 = toCharSet(first);
    std::set<char> set2 = toCharSet(second);
    std::set<char> set3 = toCharSet(third);

    std::vector<char> intermediate;
    std::vector<char> intersection;

    std::set_intersection(set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        std::back_inserter(intermediate));

    std::set_intersection(intermediate.begin(), intermediate.end(),
        set3.begin(), set3.end(),
        std::back_inserter(intersection));

    assert(intersection.size() == 1);

    return intersection[0];
}

int main() {
	cout << "AoC 2022 Day 03 part2" << endl;

    test();

    ifstream input("Day03.txt");

    int points = 0;

    while (input) {
        string line1;
        string line2;
        string line3;

        getline(input, line1);

        //assuming number of lines can be divided by 3
        if (line1.length() == 0)
            break;

        getline(input, line2);
        getline(input, line3);


        cout << "Element1: " << line1 << endl;
        cout << "Element2: " << line2 << endl;
        cout << "Element3: " << line3 << endl;

        char c = getRepeated(line1, line2, line3);
        int priority = getPriority(c);

        cout << "Repeated: " << c << "(" << priority << ")" << endl;

        points += priority;
    }

    cout << "Total points: " << points << endl;

    return 0;
}