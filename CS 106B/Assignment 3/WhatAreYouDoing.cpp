#include "WhatAreYouDoing.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
#include <cctype>
using namespace std;

/* TODO: Read the comments in WhatAreYouDoing.h to see what this function needs to do, then
 * delete this comment.
 *
 * Don't forget about the tokenize function defined in WhatAreYouDoing.h; you'll almost
 * certainly want to use it.
 */


Set<string> allEmphasesOfRec(const Vector<string>& words, const string& sentence);


Set<string> allEmphasesOfRec(const Vector<string>& words, const string& sentence){
    Set<string> emphasized;
    //if theres no more words to capitalize return a set w sentence
    if(words.isEmpty()){
        return {sentence};
    }else{
        //seperate the first word in the lsit from the rest
        Vector<string> remainder = words.subList(1);
        string word = words.first();
        //if first character is a letter (first word is a word)
        if(isalpha(word[0])){
            //add the capitalized/lowercase word to sentence and repeat
            //with the remaining words
            string sentenceUpper = sentence + toUpperCase(word);
            string sentenceLower = sentence + toLowerCase(word);
            emphasized += allEmphasesOfRec(remainder, sentenceUpper);
            emphasized += allEmphasesOfRec(remainder, sentenceLower);
        }else{
            //leave uncapitalized, check next word
            emphasized += allEmphasesOfRec(remainder, sentence + word);
        }
    }
    return emphasized;
}

Set<string> allEmphasesOf(const string& sentence) {
    Vector<string> words = tokenize(sentence);
    return allEmphasesOfRec(words, "");

}



/*
set<string> allEmphasesOfRec(const Vector<string>& words, set<string>& emphases){

    if(words.isEmpty()){
        return {};
    }
    string word = words.first();
    Vector<string> remainder = words.subList(1, words.size()-1);
    //if first character is a letter
    if(isalpha(word[0])){
        emphases += str({toUpperCase(word)} + allEmphasesOfRec(remainder, emphases));
        emphases += str({toLowerCase(word)} + allEmphasesOfRec(remainder, emphases));
    }
    //leave uncapitalized
    emphases += str({word} + allEmphasesOfRec(remainder, emphases));
    return emphases;
} */

/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Provided Test: Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Provided Test: Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Provided Test: Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

PROVIDED_TEST("Provided Test: Stress Test: Recursion only branches on words.") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}
