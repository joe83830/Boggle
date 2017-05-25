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

    if (word.length() >= 4 && dic.contains(toLowerCase(word)) && !alreadyFoundSet.contains(word)){

        return true;
    } else {

        cout << "You must enter an unfound 4+ letter word from the dictionary." << endl;
        return false;
    }
    return false;
}

bool Boggle::searchHumanWord(int x2, int y2, string word, string currentWord2){


    //        for (int row = 0; row < isOccupiedHuman.numRows(); row++){

    //            for (int col = 0; col < isOccupiedHuman.numCols(); col++){

    //                cout << isOccupiedHuman.get(row, col);
    //            }
    //            cout << endl;
    //        }
    //        cout << "-------top--------" << endl;

    if (b.inBounds(x2, y2) && isOccupiedHuman.get(x2, y2) == false){

        currentWord2 = currentWord2 + b.get(x2, y2);

        int indexOfWord = currentWord2.length() - 1;

        if (currentWord2 == word){

            for (int row = 0; row < isOccupiedHuman.numRows(); row++){                //If Found word, reset the bool grid

                for (int col = 0; col < isOccupiedHuman.numCols(); col++){

                    isOccupiedHuman.set(row, col, false);
                }

            }

            BoggleGUI::setHighlighted(x2, y2, true);
            return true;

        } else if (currentWord2.substr(indexOfWord, 1) == word.substr(indexOfWord, 1)) {

            BoggleGUI::setHighlighted(x2, y2, true);
            BoggleGUI::setAnimationDelay(100);

            isOccupiedHuman.set(x2, y2, true);

            return (searchHumanWord(x2 + 1, y2, word, currentWord2) || searchHumanWord(x2 - 1, y2, word, currentWord2) ||
                    searchHumanWord(x2 + 1, y2 + 1, word, currentWord2) || searchHumanWord(x2 + 1, y2 - 1, word, currentWord2) ||
                    searchHumanWord(x2 - 1, y2 + 1, word, currentWord2) || searchHumanWord(x2 - 1, y2 - 1, word, currentWord2) ||
                    searchHumanWord(x2, y2 + 1, word, currentWord2) || searchHumanWord(x2, y2 - 1, word, currentWord2));

            isOccupiedHuman.set(x2, y2, false);

        }

        return false;
    }

    return false;
}

bool Boggle::humanWordSearch(string word) {

    for (int row = 0; row < b.numRows(); row ++){

        for (int col = 0; col < b.numCols(); col ++){

            if (searchHumanWord(row, col, word, currentWord2) == true){

                alreadyFound.add(word);             //Vector for setting score
                alreadyFoundSet.add(word);          //Set for checking contain
                return true;
            } else {

                for (int row = 0; row < isOccupiedHuman.numRows(); row++){

                    for (int col = 0; col < isOccupiedHuman.numCols(); col++){

                        isOccupiedHuman.set(row, col, false);
                    }

                }

                BoggleGUI::clearHighlighting();   //Is this right?
            }
        }
    }

    return false;
}

int Boggle::getScoreHuman() {

    for (int i = countAssist; i < alreadyFound.size(); i ++){

        string tempWords = alreadyFound.get(i);

        humanCount += (tempWords.size() - 3);
    }

    countAssist += 1;
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

    if (b.inBounds(x, y) && isOccupied.get(x, y) == false){

        currentWord += b.get(x, y);

        if (dic.contains(currentWord) && currentWord.length() >= 4){

            addedWords.add(currentWord);
        }

        if (dic.containsPrefix(currentWord)){

            isOccupied.set(x, y, true);


            addedWords = addedWords + searchWords(x + 1, y, currentWord) +
                    searchWords(x - 1, y, currentWord) + searchWords(x, y + 1, currentWord) + searchWords(x, y - 1, currentWord) +
                    searchWords(x + 1, y + 1, currentWord) + searchWords(x + 1, y - 1, currentWord) +
                    searchWords(x - 1, y + 1, currentWord) + searchWords(x - 1, y - 1, currentWord);

            isOccupied.set(x, y, false);
        }
    }


    return addedWords;

}


int Boggle::getScoreComputer() {

    string temporaryComputerWordSearch = computerWordSearch().toString();
    Vector<string> vectorComputerWordSearchResult = stringSplit(temporaryComputerWordSearch, ", ");

    int computerScore = 0;

    int tempNum = 0;

    for (int i = 0; i < vectorComputerWordSearchResult.size(); i++){

        if (i == 0 || i == (vectorComputerWordSearchResult.size() - 1)){
            tempNum = (vectorComputerWordSearchResult[i].length() - 6);
        } else {

            tempNum = (vectorComputerWordSearchResult[i].length() - 5);
        }

        computerScore += tempNum;

    }
    return computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {

    for (int row = 0; row < boggle.b.numRows(); row++){

        for (int col = 0; col < boggle.b.numCols(); col++){

            out << boggle.b[row][col];

        }
        out << endl;
    }
    return out;
}
