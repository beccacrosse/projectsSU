/* Title: Plotter.cpp
 *
 * This code takes a stream of commands and uses it to draw
 * apicture based on the commands.
 */

#include "Plotter.h"
#include "strlib.h"
using namespace std;

/*This function takes in a Vector string containing a command, a boolean
 * dictating if pen is up/down, and a Penstyle pen
 * and alters these variables depending on the command
 */
void UpdatePen(Vector<string> command, bool& draw, PenStyle pen){
    string name = command[0];

    /*the following two statements alter the bool draw if the command
     * dictates the pen should be put down or up*/
    if(name == "pendown"){
        draw = true;
    } else if(name == "penup"){
        draw = false;
    /*the following two statements alter the color or width of the Penstyle pen
     *  if the command dictates the Penstyle width/color should be changed*/
    } else if(name == "pencolor"){
        pen.color = command[1];
    } else if(name == "penwidth"){
        pen.width = stringToReal(command[1]);
    }
}

/*This function takes in a Vector string containing a command, a boolean
 * dictating if pen is up/down, and a Penstyle pen, and two doubles that
 * represent the x and y coordinates of the pen on its screen. The
 * function alters the x, y location of the pen depending on the command
 */
void MovePen(PenStyle pen, Vector<string> command, bool draw, double& penX, double& penY){
    string name = command[0];
    double endX = stringToReal(command[1]);
    double endY = stringToReal(command[2]);
    if(command[0] == "moveabs"){
        if(draw){
            drawLine(penX, penY, endX, endY, pen);
        }
        penX = endX;
        penY = endY;
    } else{
        if(draw){
            drawLine(penX, penY, (penX + endX), (penY + endY), pen);
        }
        penX += endX;
        penY += endY;
    }
}

/*This function takes in a stream input, reads each line, and calls different
 * helper functions to draw withm move, or alter setting of the pen depending
 * on the command in each line.
 */
void runPlotterScript(istream& input) {
    PenStyle pen = {1, "black"};
    double penX = 0;
    double penY = 0;
    bool draw = false;
    for(string line; getline(input, line);){
        line = toLowerCase(line);
        Vector<string> command = stringSplit(line, " ");
        if(command.size() < 3){
            UpdatePen(command,draw, pen);
        } else{
            MovePen(pen, command, draw, penX, penY);
        }
    }
}
