#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>

template<class T> class Image
{
private:
public:
    IplImage* imgp;

    Image(IplImage* img=0)
    {
        imgp=img;
    }
    ~Image()
    {
        imgp=0;
    }
    void operator=(IplImage* img)
    {
        imgp=img;
    }
    inline T* operator[](const int rowIndx)
    {
        // renvoi l'index du debut de la ligne numero rowIndx
        return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));
    }
};

typedef struct
{
    unsigned char b,g,r;
} RgbPixel;

typedef struct
{
    float b,g,r;
} RgbPixelFloat;

typedef Image<RgbPixel>       RgbImage;
typedef Image<RgbPixelFloat>  RgbImageFloat;
typedef Image<unsigned char>  BwImage;
typedef Image<float>          BwImageFloat;

#endif // IMAGE_H_INCLUDED
