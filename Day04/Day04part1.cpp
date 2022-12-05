#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//for pair
#include <utility>

using namespace std;
using range = pair<int, int>;

pair<string, string> getPair(string s) {
    istringstream sline(s);

    pair<string, string> result;
    getline(sline, result.first, ',');
    getline(sline, result.second);

    return result;
};

range getRange(string s) {
    istringstream sline(s);

    range result;
    string temp;
    getline(sline, temp, '-');
    istringstream sfirst(temp);
    sfirst >> result.first;

    getline(sline, temp);
    istringstream ssecond(temp);
    ssecond >> result.second;

    return result;
};

//true if range1 fully contains range2
bool fullyContains(range range1, range range2) {
    return range1.first <= range2.first && range1.second >= range2.second;
};

//true if range2 starts before range1 finishes
bool overlaps(range range1, range range2) {
    return range1.first <= range2.first && range1.second >= range2.first;
}

void test() {
    pair<string, string> t;
    range r1;
    range r2;

    t = getPair("2-4,6-8");
    assert(t.first.compare("2-4") == 0);
    assert(t.second.compare("6-8") == 0);
    r1 = getRange(t.first);
    assert(r1.first == 2);
    assert(r1.second == 4);
    r2 = getRange(t.second);
    assert(r2.first == 6);
    assert(r2.second == 8);
    assert(fullyContains(r1, r2) == false);
    assert(fullyContains(r2, r1) == false);

    t = getPair("75-92,51-92");
    assert(t.first.compare("75-92") == 0);
    assert(t.second.compare("51-92") == 0);
    r1 = getRange(t.first);
    assert(r1.first == 75);
    assert(r1.second == 92);
    r2 = getRange(t.second);
    assert(r2.first == 51);
    assert(r2.second == 92);

    t = getPair("6-6,4-6");
    assert(fullyContains(getRange(t.first), getRange(t.second)) == false);
    assert(fullyContains(getRange(t.second), getRange(t.first)) == true);

    t = getPair("5-7,7-9");
    assert(overlaps(getRange(t.first), getRange(t.second)) == true);
    assert(overlaps(getRange(t.second), getRange(t.first)) == false);
}


int main() {
	cout << " AoC 2022 Day 04" << endl;

    test();

    ifstream input("Day04.txt");

    int fullyContained = 0;
    int overlap = 0;

    while (input) {
        string line;
        getline(input, line);

        if (line.length() == 0)
            break;

        pair<string, string> p = getPair(line);
        range r1 = getRange(p.first);
        range r2 = getRange(p.second);

        cout << line;

        if (fullyContains(r1, r2) || fullyContains(r2, r1)) {
            fullyContained++;
            cout << " f";
        }

        if (overlaps(r1, r2) || overlaps(r2, r1)) {
            overlap++;
            cout << " o";
        }

        cout << endl;
    }

    cout << "Fully Contained: " << fullyContained << endl; 
    cout << "Overlap: " << overlap << endl;
}