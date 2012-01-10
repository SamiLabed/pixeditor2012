#ifndef FLOU_H
#define FLOU_H

#include "image.h"

class Flou
{
public:
    Flou (float t, int ml, int mc);
    void calculMoy(int x, int y, RgbImageFloat img);
    virtual ~Flou();
protected:
private:
    float taille;
    int maxlig;
    int maxcol;
    float val;
    float** noyau;
    int rayon;
};

#endif // FLOU_H
