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

void playOneGame(Lexicon& dictionary) {

    string boardText = "";

    if (!getYesOrNo("Do you want to generate a random board?")){
        while (true){
            string boardText = toUpperCase(trim(getLine("Build your own boggle")));
            if (boardText.length() == 16){

                break;
            } else {

                cout << "Please enter 16 characters";
            }
        }
    }
    Boggle b1 = Boggle(dictionary, boardText);

    string word = getLine("Enter the words you found ");
    b1.humanWordSearch(word);

}
