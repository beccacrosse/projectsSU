#include "GUI/SimpleTest.h"
#include "error.h"
#include "vector.h"
using namespace std;

/* We've provided this function to you; you don't need to implement it. */
bool isPerfectSquare(int value);

bool hasSquareSequenceRec(Vector<int> chosenNums,
                          Vector<int> remainingNums, Vector<int>& sequence);

bool hasSquareSequence(int n, Vector<int>& sequence) {
    if(n < 1)
        error("n is out of bounds");
    if(n == 1){
        sequence.add(n);
        return true;
    }

    Vector<int> chosenNums;
    Vector<int> remainingNums;
    for(int x = 1; x <= n; x++)
        remainingNums.add(x);
    //store
    return hasSquareSequenceRec(chosenNums, remainingNums, sequence);
}

bool hasSquareSequenceRec(Vector<int> chosenNums,
                          Vector<int> remainingNums, Vector<int>& sequence){
    //if theres 1 int in sequence
    if(remainingNums.isEmpty()){
        sequence = chosenNums;
        return true;
    }else{
        //create variable to store possible combinations
        //Vector<int> possibility;
        //loop through every possible combo
        for(int i = 0; i < remainingNums.size(); i ++){
            int current = remainingNums[i];
            //if the left adjacent number is a perfect square proceed wiht recursion
            if (isPerfectSquare(current + chosenNums.last())){
                chosenNums.add(current);
                remainingNums.remove(i);
                hasSquareSequenceRec(chosenNums, remainingNums, sequence);
                //add back if path doesn't work
                chosenNums.remove(current);
                remainingNums += i;
            }
            //otherwise next int in sequence is tested in this place
        }
    }
    return false;
}

/*
bool hasSquareSequenceRec(int n, Vector<int> chosenNums,
                          Vector<int> remainingNums, Vector<int>& sequence){
    Vector<int> possibility;
    //if n is zero or negative call error
    if(n < 1)
        error("n is out of bounds");
    //if theres 1 int in sequence
    if(n == 1){
        return n;
    }else{
        //create variable to store possible combinations
        //loop through every possible combo
        for(int i = 0; i < remainingNums.size(); i ++){
            //if the left adjacent number is a perfect square proceed wiht recursion
            if (isPerfectSquare(remainingNums[i] + chosenNums[chosenNums.size()-1])){
                //removes int in use from list of ints to be used
                remainingNums.remove(i);
                //compares every possible combination of the remaining ints
                possibility += hasSquareSequenceRec(n-1, chosenNums, remainingNums, sequence);
            }
            //otherwise next int in sequence is tested in this place
            if()
        }
        //if

    }
    for(int number: possibility)
    return false;
}*/
/* Space for test cases. You are not required to write any test cases, but you
 * are encouraged to do so because our test coverage is not as extensive as what
 * you saw in Assignment 4 or the first midterm exam.
 */
