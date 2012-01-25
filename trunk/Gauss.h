#ifndef GAUSS_H
#define GAUSS_H
#include "Image.h"
class Gauss
{
public:
    Gauss(float t, int ml, int mc);
    void calcGauss(int x, int y, RgbImage img, RgbImage img2);
private:
    float taille;
    int maxlig;
    int maxcol;
    int rayon;
};

#endif // GAUSS_H
