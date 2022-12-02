#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const string oRock("A");
const string oPaper("B");
const string oScissors("C");

const string iRock("X");
const string iPaper("Y");
const string iScissors("Z");

bool isRock(string play){
    return play.compare(oRock) == 0 || play.compare(iRock) == 0;
}

bool isPaper(string play){
    return play.compare(oPaper) == 0 || play.compare(iPaper) == 0;
}

bool isScissors(string play){
    return play.compare(oScissors) == 0 || play.compare(iScissors) == 0;
}

bool areSame(string opponent, string me) {
    if ((isRock(opponent) && isRock(me))
        || (isPaper(opponent) && isPaper(me))
        || (isScissors(opponent) && isScissors(me)))
        return true;

    return false;
}

string getWinner(string opponent) {
    if (isRock(opponent))
        return iPaper;

    if(isPaper(opponent))
        return iScissors;

    if(isScissors(opponent))
        return iRock;

    assert(false);
    return "";
}

string getDraw(string opponent) {
    if (isRock(opponent))
        return iRock;

    if(isPaper(opponent))
        return iPaper;

    if(isScissors(opponent))
        return iScissors;

    assert(false);
    return "";  
}

string getLoser(string opponent) {
    if (isRock(opponent))
        return iScissors;

    if(isPaper(opponent))
        return iRock;

    if(isScissors(opponent))
        return iPaper;

    assert(false);
    return ""; 
}

int getScore(string opponent, string me)
{
    constexpr int lost = 0;
    constexpr int draw = 3;
    constexpr int win = 6;

    if (areSame(opponent, me))
        return draw;

    //opponent calls rock
    if (isRock(opponent)){
        if (isPaper(me))
            return win;
        //me can be only scissors
        return lost;
    }

    //opponent calls paper
    if (isPaper(opponent)){
        if(isScissors(me))
            return win;
        //me can be only rock 
        return lost;
    }

    //opponent calls scissors
    if (isScissors(opponent)){
        if(isRock(me))
            return win;
        //me can be only paper
        return lost;
    }

    assert(false);
    return 0;
}

int getPlayScore(string hand)
{
    if(isRock(hand))
        return 1;

    if(isPaper(hand))
        return 2;

    if(isScissors(hand))
        return 3;

    assert(false);
    return 0;
}

int main() {
	cout << " AoC 2022 Day 02" << endl;

    ifstream input("Day02.txt");

    int points = 0;

    while (input) {
        string line;
        getline(input, line);

        if (line.length() == 0)
            break;

        istringstream sline(line);

        string first;
        getline(sline, first, ' ');
        string second;
        getline(sline, second, ' ');
        
        if (second.compare("X") == 0)
            second = getLoser(first);
        else if (second.compare("Y") == 0)
            second = getDraw(first);
        else if (second.compare("Z") == 0)
            second = getWinner(first);
        else
            assert(false); //this should never happen
        
        int score = getScore(first, second);
        int playScore = getPlayScore(second);

        points += score + playScore;

        cout << "Game: " << score << " Hand: " << playScore << " Total: " << points << endl;
    }

    return 0;
}