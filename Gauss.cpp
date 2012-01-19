#include "Gauss.h"

Gauss::Gauss(float t, int ml, int mc)
{
    taille = t;
    maxlig = ml;
    maxcol = mc;
    rayon = taille / 2;
}

void Gauss::calcGauss(int x, int y, RgbImage img, RgbImage img2)
{
    int i, j;
    float borneMiniLig, borneMiniCol, borneMaxiLig, borneMaxiCol;
    float val;
    float resB = 0;
    float resG = 0;
    float resR = 0;


    borneMiniLig = x - rayon;
    if(borneMiniLig < 0)
        borneMiniLig = 0;

    borneMiniCol = y - rayon;
    if(borneMiniCol < 0)
        borneMiniCol = 0;

    borneMaxiLig = x + rayon;
    if(borneMaxiLig >= maxlig)
        borneMaxiLig = maxlig - 1;

    borneMaxiCol = y + rayon;
    if(borneMaxiCol >= maxcol)
        borneMaxiCol = maxcol - 1;

    for(i = borneMiniLig; i <= borneMaxiLig; i++)
    {
        for(j= borneMiniCol; j <= borneMaxiCol; j++)
        {
            if( (i == x) && (j == y) )
            {
                val = 4/16.;

            }
            else if( ((i == x + 1) && (j == y)) || ((i == x - 1) && (j == y))
                    || ((i == x) && (j == y + 1)) || ((i == x) && (j == y - 1)) )
            {
                val = 2/16.;
            }
            else
            {
                val = 1/16.;
            }
            resB += img2[i][j].b * val;
            resG += img2[i][j].g * val;
            resR += img2[i][j].r * val;
        }
    }
    img[x][y].b = resB;
    img[x][y].g = resG;
    img[x][y].r = resR;
}
