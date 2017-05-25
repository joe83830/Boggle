
#include "Boggle.h"
#include "lexicon.h"
#include <iostream>
#include <string>
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "bogglegui.h"

void playOneGame(Lexicon& dictionary) {

    BoggleGUI::initialize(4, 4);

    string boardText = "";

    if (!getYesOrNo("Do you want to generate a random board?")){

        while (true){

            boardText = toUpperCase(trim(getLine("Type the 16 letters to appear on the board: ")));

            if ((boardText.length() == 16)){

                break;

            } else {

                cout << "That is not a vali d 16-letter board string. Try again." << endl;
            }
        }
    }
    Boggle b1 = Boggle(dictionary, boardText);

    cout << b1 << endl;

    for (int row = 0; row < 4; row++){

        for (int col = 0; col < 4; col++){

            BoggleGUI::labelCube(row, col, b1.getLetter(row,col));
        }
    }

    int count = 0;

    while (true){

        string word = toUpperCase(getLine("Type a word (or Enter to stop)"));

        if (word == ""){

            break;
        }

        if (((b1.checkWord(word) == true) && (b1.humanWordSearch(word) == true))){

            count += 1;
            cout << "Your words (" << count << "):" << b1.alreadyFound << endl;
            int getScoreHumanNum = b1.getScoreHuman();
            cout << "Your Score: " << getScoreHumanNum << endl;

            BoggleGUI::setScore(getScoreHumanNum, BoggleGUI::HUMAN);
        }
    }

    b1.countAssist = 0;

    cout << "It's my turn!" << endl;
    cout << "My words (" << b1.computerWordSearch().size() << "): " << b1.computerWordSearch().toString() << endl;

    int getScoreComputerNum = b1.getScoreComputer();
    cout << "My score: " << getScoreComputerNum << endl;
    BoggleGUI::setScore(getScoreComputerNum, BoggleGUI::COMPUTER);

}
