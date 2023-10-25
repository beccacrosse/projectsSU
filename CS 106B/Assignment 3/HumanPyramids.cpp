#include "HumanPyramids.h"
#include "GUI/SimpleTest.h"
#include "map.h"
#include "gridlocation.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */

//this points to a helper function that determines if a row/col pair is in bounds
//of a pyramid of a certain height
bool inBounds(int row, int col, int height);

double weightOnBackRec(int row, int col, int pyramidHeight, Map<GridLocation, double>& table){
    GridLocation xy = GridLocation(row, col);
    if(pyramidHeight == 0 || row == 0){
        return 0;
    }else if(table[xy] != 0){
        return table[xy];
    }
    else{
        double weightTotal = 0;
        if(col == 0){
             weightTotal += .5 * (160 + weightOnBackRec(row-1 , col, pyramidHeight, table));
        }
        else if(col == row){
            weightTotal += .5 * (160 + weightOnBackRec(row-1 , col-1, pyramidHeight, table));
        }
        else{
            weightTotal += .5 * (160 + weightOnBackRec(row-1 , col, pyramidHeight, table));
            weightTotal += .5 * (160 + weightOnBackRec(row-1 , col-1, pyramidHeight, table));
        }
        table[xy] = weightTotal;
        return weightTotal;
    }
}

double weightOnBackOf(int row, int col, int pyramidHeight) {
   Map<GridLocation, double> table;
   if(!inBounds(row, col, pyramidHeight) || pyramidHeight < 0 ){
       error("This column/row is out of bounds");
   }
   return weightOnBackRec(row, col, pyramidHeight, table);
}

/*This function takes in a row and column pair and a height
 * and returns a bool if the row/colum is within bounds of a
 * pyramid of the inputed height */
bool inBounds(int row, int col, int height){
    if(row < 0 || row > height || col <0 || col > row){
        return false;
    }
    return true;
}




/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

STUDENT_TEST("checks person A from the handout (correctly predicts base case"){
    EXPECT_EQUAL(weightOnBackOf(0, 0, 5), 0);
}

STUDENT_TEST("Check person D from handout (side person)"){
    EXPECT_EQUAL(weightOnBackOf(2, 0, 5), 120);
}



/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented.") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    //SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
