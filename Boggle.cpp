// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "bogglegui.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};



Boggle::Boggle(Lexicon& dictionary, string boardText) {


    b = Grid<char>(4,4);

    if (boardText == ""){
        for (int row = 0; row < 4; row ++){

            for (int col = 0; col < 4; col ++){

                int col2 = col + row * 4;
                int randomchar = randomInteger(0, 5);
                string extract = CUBES[col2].substr(randomchar, 1);
                char extract2 = stringToChar(extract);
                this->b.set(row, col, extract2);

            }
        }
    } else{

        for (int row = 0; row < 4; row ++){

            for (int col = 0; col < 4; col ++){

                int num = col + row * 4;
                char stuff = stringToChar(boardText.substr(num, 1));
                this->b.set(row, col, stuff);
            }
        }
    }

    dic = dictionary;

}

char Boggle::getLetter(int row, int col) {


    if(!b.inBounds(row, col)){

        throw 0;  //丟到外面再一口氣抓

    } else{

        return b[row][col];
    }
}

bool Boggle::checkWord(string word) {

    if (word.length() >= 4 && dic.contains(toLowerCase(word)) && !alreadyFound.contains(word)){

        return true;
    } else {

        return false;
    }
}

bool Boggle::searchHumanWord(int x2, int y2, string word, string currentWord2){

    if (!b.inBounds(x2, y2)){

        return false;
    } else {

        currentWord2 = currentWord2 + b.get(x2, y2);

        if (dic.contains(currentWord2)){

            return true;
        } else if (dic.containsPrefix(currentWord2)) {

            return (searchHumanWord(x2 + 1, y2, word, currentWord2) || searchHumanWord(x2 - 1, y2, word, currentWord2) ||
                    searchHumanWord(x2 + 1, y2 + 1, word, currentWord2) || searchHumanWord(x2 + 1, y2 - 1, word, currentWord2) ||
                    searchHumanWord(x2 - 1, y2 + 1, word, currentWord2) || searchHumanWord(x2 - 1, y2 - 1, word, currentWord2) ||
                    searchHumanWord(x2, y2 + 1, word, currentWord2) || searchHumanWord(x2, y2 - 1, word, currentWord2));
        }

        return false;
    }
}

bool Boggle::humanWordSearch(string word) {

    for (int row = 0; row < b.numRows(); row ++){

        for (int col = 0; col < b.numCols(); col ++){

            if (searchHumanWord(row, col, word, currentWord2) == true){

                alreadyFound.add(word);
                return true;
            }
        }
    }


    return false;
}

int Boggle::getScoreHuman() {

    for (int i = 0; i < alreadyFound.size(); i ++){

        string tempWords = alreadyFound.get(i);
        humanCount += (tempWords.size() - 3);
    }
    return humanCount;
}

Set<string> Boggle::computerWordSearch() {

    Set<string> result;

    for (int x = 0; x < b.numRows(); x ++){

        for (int y = 0; y < b.numCols(); y ++){

            result = result + searchWords(x, y, currentWord);
        }
    }

    return result;
}

Set<string> Boggle::searchWords(int x, int y, string currentWord){

    Set<string> addedWords;

    isOccupied.set(x, y, false);

    if (isOccupied.get(x, y)){
        if (!b.inBounds(x, y)){

            return addedWords;

        } else {

            currentWord + b.get(x, y);
            if (dic.contains(currentWord)){

                addedWords.add(currentWord);
            }

            if (dic.containsPrefix(currentWord)){

                searchWords(x, y, currentWord) = addedWords + searchWords(x + 1, y, currentWord) +
                        searchWords(x - 1, y, currentWord) + searchWords(x, y + 1, currentWord) + searchWords(x, y - 1, currentWord) +
                        searchWords(x + 1, y + 1, currentWord) + searchWords(x + 1, y - 1, currentWord) +
                        searchWords(x - 1, y + 1, currentWord) + searchWords(x - 1, y - 1, currentWord);
            }
        }
    }

    currentWord = "";
    return addedWords;

}


int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
