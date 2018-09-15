//
// Created by wil98 on 2017-06-14.
//
#include "Draw.h"

static unsigned char strokeR = 0;
static unsigned char strokeG = 0;
static unsigned char strokeB = 0;

static unsigned char fillR = 0;
static unsigned char fillG = 0;
static unsigned char fillB = 0;

static char isStroke = 1;
static char isFill = 0;

void setStrokeColor(unsigned char r, unsigned char g, unsigned char b)
{
    strokeR = r;
    strokeG = g;
    strokeB = b;
}

void setFillColor(unsigned char r, unsigned char g, unsigned char b)
{
    fillR = r;
    fillG = g;
    fillB = b;
}

void setIsStroke(char state)
{
    isStroke = state;
}

void setIsFill(char state)
{
    isFill = state;
}

void arc(Image*image, int x, int y, int w, int h, double s, double e)
{
    // TODO FILL
    int colorChanged = 0;
    int a = w;
    int b = h;
    do
    {
        for (float theta = s; theta < e; theta += 0.001) {
            int pa = a;
            int pb = b;

            if (pa <= 0)
                pa = 0;

            if (pb <= 0)
                pb = 0;

            int px = (int) round(x + pa * cos(theta));
            int py = (int) round(y + pb * sin(theta));

            if (isStroke && a == w && b == h) {
                setPixelColor(image, px, py, strokeR, strokeG, strokeB);
            }
            else if (isFill)
            {
                setPixelColor(image, px, py, fillR, fillG, fillB);
            }
            else
            {
                return;
            }
        }
        a -= 1;
        b -=1;
    } while((a >= 0 || b >= 0) && isFill);
}

void ellipse(Image*image, int x, int y, int w, int h)
{
    arc(image, x, y, w, h, 0, 2 * M_PI);
}

void circle(Image*image, int x, int y, int r)
{
    ellipse(image, x, y, r, r);
}

void line(Image*image, int x1, int y1, int x2, int y2)
{
    if (!isStroke)
        return;

    int yMin = MIN2(y1, y2);
    int yMax = MAX2(y1, y2);

    if (x1 == x2)
    {
        for (int y = yMin; y < yMax; ++y)
        {
            setPixelColor(image, x1, y, strokeR, strokeG, strokeB);
        }
    }
    else
    {
        int xMin = MIN2(x1, x2);
        int xMax = MAX2(x1, x2);

        float m = (float) (y2 - y1) / ((x2 - x1));
        float b = y1 - m * x1;

        for (int x = xMin; x < xMax; ++x)
        {
            setPixelColor(image, x, (int)(x*m + b), strokeR, strokeG, strokeB);
        }
    }
}

void point(Image*image, int x, int y)
{
    if (!isStroke)
        return;
    setPixelColor(image, x, y, strokeR, strokeG, strokeB);
}

void quad(Image*image, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    if (isFill)
    {
        int tmp = isStroke;
        setIsStroke(0); // don't draw lines of triangles
        triangle(image, x1, y1, x2, y2, x3, y3);
        triangle(image, x3, y3, x4, y4, x1, y1);
        setIsStroke(tmp);
    }
    if (isStroke)
    {
        line(image, x1, y1, x2, y2);
        line(image, x2, y2, x3, y3);
        line(image, x3, y3, x4, y4);
        line(image, x4, y4, x1, y1);
    }
}

void rect(Image* image, int x1, int y1, int x2, int y2)
{
    // Could have used two triangles, but faster that way
    int minX = MIN2(x1, x2);
    int maxX = MAX2(x1, x2);

    int minY = MIN2(y1, y2);
    int maxY = MAX2(y1, y2);

    for (int x = minX; x < maxX; ++x)
    {
        for (int y = minY; y < maxY; ++y)
        {
            setPixelColor(image, x, y, strokeR, strokeG, strokeB);
        }
    }
}

void roundRect(Image*image, int x1, int y1, int x2, int y2, int tl, int tr, int br, int bl)
{
    // TODO
}

void triangle(Image*image, int x1, int y1, int x2, int y2, int x3, int y3)
{
    // FIXME fix for narrow triangle
    if (isFill)
    {
        int xMin = MIN3(x1, x2, x3);
        int xMax = MAX3(x1, x2, x3);

        int yMin = MIN3(y1, y2, y3);
        int yMax = MAX3(y1, y2, y3);

        for (int x = xMin; x < xMax; ++x)
        {
            for (int y = yMin; y < yMax; ++y)
            {
                // http://mathworld.wolfram.com/TriangleInterior.html
                // A = (x1, y1)
                // B = (x2, y2)
                // C = (x3, y3)
                // P = (x, y)
                int v0x = x1;
                int v0y = y1;

                // A -> B
                int v1x = x2 - x1;
                int v1y = y2 - y1;

                // A -> C
                int v2x = x3 - x1;
                int v2y = y3 - y1;

                double deno = v1x*v2y - v1y*v2x;

                double a =  ((double)(x*v2y - y*v2x) - (v0x*v2y - v0y*v2x)) / deno;

                if (a < 0.0)
                    continue;

                double b = -((double)(x*v1y - y*v1x) - (v0x*v1y - v0y*v1x)) / deno;

                if (b < 0.0 || a + b > 1.0)
                    continue;

                // continue's are used to saved some calculations
                //if (a > 0 && b > 0 && a+b < 1)    setPixelColor(image, x, y, fillR, fillG, fillB);
                setPixelColor(image, x, y, fillR, fillG, fillB);
            }
        }
    }
    if (isStroke)
    {
        line(image, x1, y1, x2, y2);
        line(image, x2, y2, x3, y3);
        line(image, x3, y3, x1, y1);
    }
}
