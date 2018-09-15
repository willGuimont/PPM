#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "Pixel.h"
#include "Draw.h"
#include "Macro.h"

int main()
{
    Image*image = createImage(100, 100, COLOR, 255);

    FILE* file = fopen("test2.ppm", "w");
    if (!file)
        printf("Error: %s\n", strerror(errno));

    setIsStroke(1);
    setIsFill(1);
    setStrokeColor(255, 255, 255);
    setFillColor(255, 0, 255);

    ellipse(image, 50, 50, 50, 10);

    writeImageToFile(file, image);

    fclose(file);

    deleteImage(image);
}
