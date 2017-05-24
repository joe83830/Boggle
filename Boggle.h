// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    Set<string> searchWords(int x, int y, string currentWord);
    bool searchHumanWord(int x2, int y2, string word, string currntWord2);

private:
    Grid<char> b;
    Lexicon dic;
//    int x = 0;
//    int y = 0;
//    int x2 = 0;
//    int y2 = 0;
    string currentWord = "";
    string currentWord2 = "";
    Grid<bool> isOccupied = Grid<bool>(4, 4, true);

};

#endif // _boggle_h
