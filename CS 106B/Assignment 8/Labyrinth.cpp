/*
 * This code implements a game where users find a path
 * to escape a labyrinth of pointers by collecting 3 items
 * stored within the pointer labyrinth
 *
 */
#include "Labyrinth.h"
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"
#include "set.h"
using namespace std;

/* This function takes in a MazeCell* starting location and a string of
 * directions to move, traverses the pointers represented by each direction
 * in the string and returns a bool if it is possible to collect the items
 * needed to escape the maze given the inputed set of moves
 */
bool isPathToFreedom(MazeCell* start, const string& moves) {
    /* TODO: Delete this comment and the next few lines, then implement
     * this function. run through every string
     * check if you can move in da direction
     * check if it has an item where u move
     */
    Set<Item> items = {};
    Item theItem = start->whatsHere;
    for(char move: moves){
        theItem = start->whatsHere;
        if (theItem != Item::NOTHING){
             items.add(theItem);
         }
        if (move == 'N' && start->north != nullptr)
            start = start->north;
        else if (move == 'E' && start->east != nullptr)
            start = start->east;
        else if (move == 'W' && start->west != nullptr)
            start = start->west;
        else if (move == 'S' && start->south != nullptr)
            start = start->south;
        else
            return false;
    }
    theItem = start->whatsHere;
    if (theItem != Item::NOTHING){
         items.add(theItem);
     }
    return items.size() == 3;
}


/* * * * * * Test Cases Below This Point * * * * * */

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we delete maze, or empty maze, or something
     * along those lines?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

