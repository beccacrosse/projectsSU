#include "Sierpinski.h"
#include "error.h"
using namespace std;

/**
 * Draws a triangle with the specified corners in the specified window. Feel free
 * to edit this function as you see fit to change things like color, fill style,
 * etc. in whatever way you'd like!
 *
 * @param window The window in which to draw the triangle.
 * @param x0 y0 The first corner of the triangle.
 * @param x1 y1 The second corner of the triangle.
 * @param x2 y2 The third corner of the triangle.
 */
void drawTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2) {
    window.setColor("black");
    window.fillPolygon({ x0, y0, x1, y1, x2, y2 });
}
//Thisn points to a helper function which returns
//the midpoint of two doubles
double midpoint(double x, double y);


/* TODO: Refer to Sierpinski.h for more information about what this function should do.
 * Then, delete this comment.
 */
void drawSierpinskiTriangle(GWindow& window,
                            double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int order) {
    if(order <0)
        error("Order cannot be less than zero");
    if(order == 0){
        drawTriangle(window, x0, y0, x1, y1, x2, y2);
    }
    else{
        //represents the midpoint between x0,y0 and x1,y1 (left)
        double midpointAX = midpoint(x0, x1);
        double midpointAY = midpoint(y0, y1);
        //represents the midpoint between x1,y1 and x2,y2(right)
        double midpointBX = midpoint(x1, x2);
        double midpointBY = midpoint(y1, y2);
        //represents the midpoint between x2,y2 and x0,y0(bottom
        double midpointCX = midpoint(x2, x0);
        double midpointCY = midpoint(y2, y0);

        //draw smaller triangle with points at midpoints
        //left triangle
        drawSierpinskiTriangle(window, x0, y0, midpointAX, midpointAY,
                               midpointCX, midpointCY, order-1);
        //right triangle
        drawSierpinskiTriangle(window, midpointAX, midpointAY,
                               x1, y1, midpointBX, midpointBY,  order-1);
        //top triangle
        drawSierpinskiTriangle(window, midpointCX, midpointCY,
                             x2, y2, midpointBX, midpointBY, order-1);
    }
}

//This function takes in two doubles and returns their midpoint
double midpoint(double x, double y){
    return (x+y)/ 2;
}
