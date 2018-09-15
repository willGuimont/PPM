//
// Created by wil98 on 2017-06-14.
//

#ifndef PPM_DRAW_H
#define PPM_DRAW_H

#include "Pixel.h"
#include "Macro.h"

static unsigned char strokeR;
static unsigned char strokeG;
static unsigned char strokeB;

static unsigned char fillR;
static unsigned char fillG;
static unsigned char fillB;

static char isStroke;
static char isFill;

/*
 * Change the stroke color (line)
 */
void setStrokeColor(unsigned char r, unsigned char g, unsigned char b);
/*
 * Change the fill color (inside of the shape)
 */
void setFillColor(unsigned char r, unsigned char g, unsigned char b);
/*
 * Enable or disable stroke
 */
void setIsStroke(char state);
/*
 * Enable of disable fill
 */
void setIsFill(char state);

/*
 * Draw an arc
 * (x, y)   = center fo the arc
 * w        = width of the ellipse
 * h        = height of the ellipse
 * s        = angle to start the arc (rad)
 * e        = angle to end the arc (rad)
 */
void arc(Image*image, int x, int y, int w, int h, double s, double e);
/*
 * Draw an ellipse
 * (x, y)   = center fo the arc
 * w        = width of the ellipse
 * h        = height of the ellipse
 */
void ellipse(Image*image, int x, int y, int w, int h);
/*
 * Draw a circle
 * (x, y)   = center fo the arc
 * r        = radius
 * Equivalent to ellipse(image, x, y, r, r);
 */
void circle(Image*image, int x, int y, int r);
/*
 * Draw a line between two points
 * (x1, y1) = start point
 * (x2, y2) = end point
 */
void line(Image*image, int x1, int y1, int x2, int y2);
/*
 * Draw a point
 * (x, y)   = point
 */
void point(Image*image, int x, int y);
/*
 * (xn, yn) = coordinates of points of the quad in order
 */
void quad(Image*image, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
/*
 * Draw a rect
 * (x1, y1) = top left corner
 * (x2, y2) = bottom right corner
 */
void rect(Image* image, int x1, int y1, int x2, int y2);
/*
 * Draw a rect with round corners
 * (x1, y1) = top left corner
 * (x2, y2) = bottom right corner
 * tr       = radius of top right corner
 * tl       = radius of top left corner
 * br       = radius of bottom right corner
 * bl       = radius of bottom left corner
 */
void roundRect(Image*image, int x1, int y1, int x2, int y2, int tl, int tr, int br, int bl);
/*
 * Draw a triangle
 * (xn, yn) = coordinates of points if the triangle
 */
void triangle(Image*image, int x1, int y1, int x2, int y2, int x3, int y3);

#endif //PPM_DRAW_H
