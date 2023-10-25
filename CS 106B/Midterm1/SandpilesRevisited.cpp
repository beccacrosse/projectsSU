#include "GUI/SimpleTest.h"
#include "grid.h"
using namespace std;

/* %% Place all the code you want us to grade below this line. Do not edit this comment. %% */


int dropSandOnRec(Grid<int>& world, int row, int col, int& topples);

int dropSandOn(Grid<int>& world, int row, int col) {
    int topples = 0;
    return dropSandOnRec(world, row, col, topples);
}

int dropSandOnRec(Grid<int>& world, int row, int col, int& topples) {
    if(world.inBounds(row, col)){
        if(world[row][col] < 3)
           world[row][col] += 1;

        else{
            //updates amount of topples
            topples += 1;
            /*empties current cell
             * drops  sand to position row+1, row-1, col+1, col-1
             * (AKA directly above, below, to the left, and to the
             * right of the current sand location */
            world[row][col] = 0;
            dropSandOnRec(world, row+1, col, topples); //space below
            dropSandOnRec(world, row-1, col, topples); //space above
            dropSandOnRec(world, row, col+1, topples); //space to the right
            dropSandOnRec(world, row, col-1, topples); //space to the left
        }
    }
    return topples;
}




/* %% Place all the code you want us to grade above this line. Do not edit this comment. %% */




/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping onto an empty cell causes no topples.") {
    /* A simple source grid. */
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

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 0);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Dropping out of bounds causes no topples.") {
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };

    /* Nothing should change when dropping sand out of bounds. */
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };

    EXPECT_EQUAL(dropSandOn(before, 3, 3), 0);
    EXPECT_EQUAL(before, after);

    EXPECT_EQUAL(dropSandOn(before, -137, -42), 0);
    EXPECT_EQUAL(before, after);

    EXPECT_EQUAL(dropSandOn(before, 0, 9), 0);
    EXPECT_EQUAL(before, after);
}

PROVIDED_TEST("Dropping onto a cell with one sand grain causes no topples.") {
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 2, 3 },
        { 3, 3, 3 }
    };

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 0);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Dropping onto a cell with two sand grains causes no topples.") {
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 2, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 3, 3 },
        { 3, 3, 3 }
    };

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 0);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Correctly counts a non-chaining topple.") {
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

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Counts two chaining topples.") {
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

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 2);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Counts a large number of chained topples.") {
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        {1, 2, 1},
        {1, 3, 1}
    };

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 6);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Counts topples that repeat at a cell.") {
    Grid<int> before = {
        { 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3 },
    };

    EXPECT_EQUAL(dropSandOn(before, 1, 1), 74);
}








