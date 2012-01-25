#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <stdio.h>

template<class T> class Image
{
private:
public:
    int nblignes;
    int nbcolonnes;
    QImage* imgexe;

    Image(QImage* img=0)
    {
        imgexe = img;
    }
    ~Image()
    {
        imgexe=0;
    }
    void operator=(QImage* img)
    {
        imgexe=img;
    }
    inline T* operator[](const int rowIndx)
    {
        // renvoi l'index du debut de la ligne numero rowIndx
        return ( (T *) (imgexe->scanLine(rowIndx)) );
    }
};

typedef struct
{
    unsigned char b,g,r,alpha;
} RgbPixel;

typedef Image<RgbPixel> RgbImage;

#endif // IMAGE_H
