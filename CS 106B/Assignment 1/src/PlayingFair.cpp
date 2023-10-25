/* File: PlayingFair.cpp
 *
 * As a system for fairly picking members of a team A and B,
 * despite which team picks first:
 * This code takes in a positive integer n and constructs a
 * sequence with A's and B's to represent each team's turn
 */
#include "PlayingFair.h"
#include "GUI/SimpleTest.h"
#include "error.h"
using namespace std;

/* This points to the function opposite*/
string makeOpposite(string letters);


/* This code takes in a positive integer n and constructs a
 * sequence with A's and B's to represent each team A and B,
 * starting with A
 */
string aSequenceOfOrder(int n) {
    if (n < 0) {
        error("ERROR: Negative integers are not allowed");
    } else if (n == 0){
        return "A";
    } else {
        return aSequenceOfOrder(n-1) + makeOpposite(aSequenceOfOrder(n-1));
    }
}


/* This code takes in a positive integer n and constructs a
 * sequence with A's and B's to represent each team A and B,
 * starting with B
 */
string bSequenceOfOrder(int n) {
    if (n < 0) {
        error("ERROR: Negative integers are not allowed");
    } else if (n == 0) {
        return "B";
    } else {
        return bSequenceOfOrder(n-1) + makeOpposite(bSequenceOfOrder(n-1));
    }
}

/* This code takes in a string containing A's and B's and returns it
 * it with every charactrer is the opposite of the original string
 * where the opposite of A = B and the opposite of B = A
 */
string makeOpposite(string letters){
    if (letters == ""){
        return "";
    }
    else if (charToString(letters[0]) == "A"){
        return "B" + makeOpposite(letters.substr(1));
    } else {
        return "A" + makeOpposite(letters.substr(1));
    }
}



/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Sequences of order 3 are correct.") {
    /* Some very basic checks. */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

PROVIDED_TEST("Only characters should be As and Bs.") {
    for (int i = 0; i < 10; i++) {
        for (char ch: aSequenceOfOrder(i)) {
            EXPECT(ch == 'A' || ch == 'B');
        }
    }
}

PROVIDED_TEST("A-sequence of positive order should have equal As and Bs.") {
    /* Exclude the sequence of order 0, which is just a single character. */
    for (int i = 1; i < 10; i++) {
        int as = 0;
        int bs = 0;
        for (char ch: aSequenceOfOrder(i)) {
            if (ch == 'A') as++;
            else bs++;
        }

        EXPECT_EQUAL(as, bs);
    }
}

PROVIDED_TEST("Triggers error on negative inputs.") {
    /* The EXPECT_ERROR macro expects the given expression to call error(). Remember that
     * you need to guard against invalid inputs.
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
}


STUDENT_TEST("tests that opposite function returns an opposite"){
    EXPECT_EQUAL(makeOpposite("B"), "A");
    EXPECT_EQUAL(makeOpposite("BA"), "AB");
    EXPECT_EQUAL(makeOpposite("ABBABAAB"), "BAABABBA");
}

STUDENT_TEST("Handles sequences of order 0."){
    EXPECT_EQUAL(aSequenceOfOrder(0), "A");
    EXPECT_EQUAL(bSequenceOfOrder(0), "B");
}








