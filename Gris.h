#ifndef GRIS_H
#define GRIS_H
#include <QImage>
#include "Image.h"

class Gris
{
public:
   Gris(int ml, int mc);
   void calNivGris(RgbImage image);
protected:
private:
    int maxlig;
    int maxcol;
};

#endif // GRIS_H

