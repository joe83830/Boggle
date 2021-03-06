
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

    friend ostream& operator<<(ostream& out, Boggle& boggle);
    Set<string> searchWords(int x, int y, string currentWord);
    bool searchHumanWord(int x2, int y2, string word, string currntWord2);
    Grid<char> b;
    Vector<string> alreadyFound;
    Set<string> alreadyFoundSet;
    int countAssist = 0;

private:
    Lexicon dic;
//    int x = 0;
//    int y = 0;
//    int x2 = 0;
//    int y2 = 0;
    string currentWord = "";
    string currentWord2 = "";
    Grid<bool> isOccupied = Grid<bool>(4, 4, false);
    Grid<bool> isOccupiedHuman = Grid<bool>(4, 4, false);

    int humanCount = 0;
    Vector<string> computerWordSearchVec;

};

#endif // _boggle_h
