// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "lexicon.h"
#include <iostream>
#include <string>
#include "random.h"
#include "simpio.h"
#include "strlib.h"

//int a = 0;
//Vector<char> assist;
//bool checkBoardText(int a, Vector<char> assist);
//void checkBoardTextAssist(string boardText);

void playOneGame(Lexicon& dictionary) {

    string boardText = "";

    if (!getYesOrNo("Do you want to generate a random board?")){

        while (true){

            boardText = toUpperCase(trim(getLine("Type the 16 letters to appear on the board: ")));

            if ((boardText.length() == 16)){  //Add one more filter

                break;

            } else {

                cout << "That is not a vali d 16-letter board string. Try again." << endl;
            }
        }
    }
    Boggle b1 = Boggle(dictionary, boardText);

    cout << b1 << endl;

    int count = 0;


    //For testing purposes
    cout << "My words (" << b1.computerWordSearch().size() << "): " << b1.computerWordSearch().toString() << endl;

    while (true){

        cout << "Your words (" << count << "):" << b1.alreadyFound << endl;
        string word = toUpperCase(getLine("Type a word (or Enter to stop)"));

        if (word == ""){

            break;
        }

        //Testing purposes
//        cout << "checkword" << b1.checkWord(word) << endl;
//        cout << "humanwordsearch" << b1.humanWordSearch(word) << endl;
        if (((b1.checkWord(word) == true) && (b1.humanWordSearch(word) == true))){

            count += 1;

            cout << "Your Score: " << b1.getScoreHuman() << endl;
        } else {

            cout << "Invalid input, try again " << endl;
        }

    }

    cout << "It's my turn!" << endl;
    cout << "My words (" << b1.computerWordSearch().size() << "): " << b1.computerWordSearch().toString() << endl;
}

//void checkBoardTextAssist(string boardText, Vector<char> assist){

//    for (int i = 0; i < boardText.length(); i++){

//        assist.add(boardText[i]);
//    }
//}

//bool checkBoardText(int a, Vector<char> assist){

//    if ((a < assist.size()) && (isdigit(assist.get(a)) == false)){

//        return (true && checkBoardText(a + 1, assist));
//    } else {

//        return false;
//    }
//}
