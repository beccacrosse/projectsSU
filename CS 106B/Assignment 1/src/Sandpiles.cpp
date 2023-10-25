/* File: Sandpile.cpp
 *
 * This code imitates sand falling by using a formula to spread grains of "sand"
 * when more than 3 grains of "sand" occupy the same x,y coordinate on a 2D grid.
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
using namespace std;


/* This function takes in a grid and coordinates to that grid, then it
 * imitates sand falling by using a formula to spread grains of "sand"
 * when more than 3 grains of "sand" occupy the same x,y coordinate of the grid. */
void dropSandOn(Grid<int>& world, int row, int col) {
    (void) world;
    if(world.inBounds(row, col)){
        if(world[row][col] < 3)
           world[row][col] += 1;

        else{
            /*empties current cell
             * drops  sand to position row+1, row-1, col+1, col-1
             * (AKA directly above, below, to the left, and to the
             * right of the current sand location */
            world[row][col] = 0;
            dropSandOn(world, row+1, col);
            dropSandOn(world, row-1, col);
            dropSandOn(world, row, col+1);
            dropSandOn(world, row, col-1);

        }
    }
}






/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

//student tests

STUDENT_TEST("Testing sand dropped in empty spot") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 0 }
    };

    dropSandOn(before, 1, 2);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

STUDENT_TEST("Testing sand dropped out of range") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    dropSandOn(before, 5, 6);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}









