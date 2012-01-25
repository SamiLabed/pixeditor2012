#ifndef REHAUSSEUR_H
#define REHAUSSEUR_H
#include "Image.h"

class Convolution
{
public:
    Convolution(int ml, int mc);
    void calculRehausse(int x, int y, RgbImage img, RgbImage img2);
    void calculGradient(int x, int y, RgbImage img, RgbImage img2);
    void buildRehausseur(float coeff);
    void buildLaplace();
    void buildGradient(int col0, int col1, int col2, float coeff);
    void buildPerso(float value[3][3]);
    void accentuation(int x, int y, RgbImage img, RgbImage img2, RgbImage resimg);
private:
    int maxlig;
    int maxcol;
    int rayon;
    float matrice[3][3];
    float Mx[3][3];
    float My[3][3];
};

#endif // REHAUSSEUR_H
