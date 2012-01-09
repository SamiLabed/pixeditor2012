#ifndef OPENCV_H_INCLUDED
#define OPENCV_H_INCLUDED

#include "cv.h"
#include "highgui.h"

#include "image.h"

typedef struct
{
    IplImage* histR;
    IplImage* histG;
    IplImage* histB;
}RgbHisto;

RgbHisto histogramme(RgbImageFloat img, int width, int height);
void PPHisto(char* chemin);

#endif // OPENCV_H_INCLUDED
