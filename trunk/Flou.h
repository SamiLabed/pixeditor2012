#ifndef FLOU_H
#define FLOU_H

#include "Image.h"

class Flou
{
public:
    Flou (float t, int ml, int mc);
    void calculMoy(int x, int y, RgbImage img, RgbImage img2);
    virtual ~Flou();
protected:
private:
    float taille;
    int maxlig;
    int maxcol;
    int rayon;
};

#endif // FLOU_H
