#include "include/Flou.h"


Flou::Flou(float t, int ml, int mc)
{
    taille = t;
    maxlig = ml;
    maxcol = mc;
    rayon = taille / 2;
    val = (1/(taille*taille));
    printf("val : %f\n", val);
    /*val = (1/9.);
    printf("new val : %f\n", val);*/
    noyau = new float* [(int)taille];
    for (int i = 0; i < (int)taille; i++)
        noyau[i] = new float[(int)taille];
}

Flou::~Flou()
{
    for (int i = 0; i < (int)taille; i++)
        delete [] noyau[i];
    delete [] noyau;
}

void Flou::calculMoy(int x, int y, RgbImageFloat img)
{
    int i, j;
    int borneMiniLig, borneMiniCol, borneMaxiLig, borneMaxiCol;
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
            resB += img[i][j].b * val;
            resG += img[i][j].g * val;
            resR += img[i][j].r * val;
        }
    }

    img[x][y].b = resB;
    img[x][y].g = resG;
    img[x][y].r = resR;
}
