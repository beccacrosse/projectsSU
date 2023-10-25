#include "GUI/SimpleTest.h"
#include "set.h"
#include "strlib.h"
#include <string>
#include <algorithm>
using namespace std;

/* %% Place all the code you want us to grade below this line. Do not edit this comment. %% */

//points to canPlacePerson function
bool canPlacePerson(string result);


Set<string> safeArrangementsOfRec(int lineLength, int numPeople, string result) {
    /* TODO: Delete this line and the next three lines, then implement this function.
    (void) lineLength;
    (void) numPeople;
    return {};
first make something that returns allthe ways to arrange ppl ignoring distancing*/
    string person = "P";
    string space = ".";
    int numSpaces = lineLength - numPeople; //do something with this
    Set<string> resultLine;
    if(lineLength == 0){
        return {result};
    }else if(numPeople < lineLength){
        return {};
    }else{
        //include a person
        if(canPlacePerson(result)){
            resultLine += safeArrangementsOfRec(lineLength -1, numPeople -1, result + person);
        }
        //exclude person
        if(numPeople > lineLength && numSpaces > lineLength){
            resultLine += safeArrangementsOfRec(lineLength -1, numPeople, result + space);
        }
        return resultLine;
    }
}


//possible if its at the start or theres 2 dots behind
bool canPlacePerson(string result){
    char person = 'P';
    char space = '.';
    if( result == ""){
        return true;
    }
    else if(result.size() == 2 && result[0] == space){
        return true;
    }
    else if(result[result.size()-1] == space && result[result.size()-1] == person){
        return true;
    }
    return false;
}

Set<string> safeArrangementsOf(int lineLength, int numPeople) {
    /* TODO: Delete this line and the next three lines, then implement this function.
    (void) lineLength;
    (void) numPeople;
    return {};
first make something that returns allthe ways to arrange ppl ignoring distancing*/
    if(numPeople < 0 || numPeople < lineLength){
        error("no!");
    }else{
        return safeArrangementsOfRec(lineLength, numPeople, "");
    }
}




/* %% Place all the code you want us to grade above this line. Do not edit this comment. %% */





/* * * * * Test Cases Below This Point * * * * */

PROVIDED_TEST("Handles one person in small lines.") {
    EXPECT_EQUAL(safeArrangementsOf(0, 1), { });
    EXPECT_EQUAL(safeArrangementsOf(1, 1), {"P"});
    EXPECT_EQUAL(safeArrangementsOf(2, 1), {"P.", ".P"});
    EXPECT_EQUAL(safeArrangementsOf(3, 1), {"P..", ".P.", "..P"});
    EXPECT_EQUAL(safeArrangementsOf(4, 1), {"P...", ".P..", "..P.", "...P"});
}

PROVIDED_TEST("Handles two people in small lines.") {
    EXPECT_EQUAL(safeArrangementsOf(0, 2), { });
    EXPECT_EQUAL(safeArrangementsOf(1, 2), { });
    EXPECT_EQUAL(safeArrangementsOf(2, 2), { });
    EXPECT_EQUAL(safeArrangementsOf(3, 2), { });
    EXPECT_EQUAL(safeArrangementsOf(4, 2), { "P..P" });
}

PROVIDED_TEST("Handles no people in small lines.") {
    EXPECT_EQUAL(safeArrangementsOf(0, 0), {""});
    EXPECT_EQUAL(safeArrangementsOf(1, 0), {"."});
    EXPECT_EQUAL(safeArrangementsOf(2, 0), {".."});
    EXPECT_EQUAL(safeArrangementsOf(3, 0), {"..."});
    EXPECT_EQUAL(safeArrangementsOf(4, 0), {"...."});
}

PROVIDED_TEST("Handles three people in small lines.") {
    EXPECT_EQUAL(safeArrangementsOf(0, 3), { });
    EXPECT_EQUAL(safeArrangementsOf(1, 3), { });
    EXPECT_EQUAL(safeArrangementsOf(2, 3), { });
    EXPECT_EQUAL(safeArrangementsOf(3, 3), { });
    EXPECT_EQUAL(safeArrangementsOf(4, 3), { });
}

PROVIDED_TEST("Handles three people in medium-sized lines.") {
    EXPECT_EQUAL(safeArrangementsOf(7, 3), { "P..P..P" });
    EXPECT_EQUAL(safeArrangementsOf(8, 3), { "P..P..P.",
                                             "P..P...P",
                                             "P...P..P",
                                             ".P..P..P" });
}

PROVIDED_TEST("Handles four people in medium-sized lines.") {
    EXPECT_EQUAL(safeArrangementsOf(12, 4), {
                     "P..P..P..P..",
                     "P..P..P...P.",
                     "P..P..P....P",
                     "P..P...P..P.",
                     "P..P...P...P",
                     "P..P....P..P",
                     "P...P..P..P.",
                     "P...P..P...P",
                     "P...P...P..P",
                     "P....P..P..P",
                     ".P..P..P..P.",
                     ".P..P..P...P",
                     ".P..P...P..P",
                     ".P...P..P..P",
                     "..P..P..P..P",
                 });
}

#include "filelib.h"
PROVIDED_TEST("Stress test: Handles ten people in a reasonably-sized line. (This should take at most a few seconds.)") {
    /* TODO: When you're ready to run the stress test, comment out the line below this one. */
    SHOW_ERROR("Stress test is disabled by default. To run it, comment out line " + to_string(__LINE__) + " of " + getTail(__FILE__) + ".");

    EXPECT_EQUAL(safeArrangementsOf(32, 10).size(), 1001);
}
