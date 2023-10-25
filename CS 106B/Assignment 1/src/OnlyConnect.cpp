/* File: OnlyConnect.cpp
 *
 * This code takes an inputed word and runs a puzzle game for the user to
 * solve by taking the inputed word and removing the non consonents from it,
 * allowing the user to guess the original word using only the consonents
 *
 * My dearest section lader: solve thispuzzle: HPPCMPS
 *
 * *hint* part of the brain responsible for storing longterm memories
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
using namespace std;

string onlyConnectize(string phrase) {
    /*This function takes as input a string, then transforms it into an Only Connect puzzle
     * by returning the same string in uppercase with all non consonent characters removed
     */
    string vowels = "AEOIUY";
    char character = toUpperCase(phrase[0]);

    if(phrase == ""){
        return "";
    }else{
        if(isalpha(character) and vowels.find(character) == string::npos){
        return charToString(character) + onlyConnectize(phrase.substr(1));
        }else{
            return onlyConnectize(phrase.substr(1));
        }
    }
}



/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}


/* This case tests how onlyConnectize reacts to
 * string inputs in languages that do not use the
 * english alphabet*/
STUDENT_TEST("Handles words in foreign alphabets") {
    EXPECT_EQUAL(onlyConnectize("你好"), "");
    EXPECT_EQUAL(onlyConnectize("ਸਤ ਸ੍ਰੀ ਅਕਾਲ"), "");
    EXPECT_EQUAL(onlyConnectize("Здраво"), "");
}






