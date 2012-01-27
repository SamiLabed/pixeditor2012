#include "Convolution.h"
#include "Gris.h"
#include <stdio.h>
#include <stdlib.h>

Convolution::Convolution(int ml, int mc)
{
    maxlig = ml;
    maxcol = mc;
    rayon = 1;
}

void Convolution::buildRehausseur(float coeff)
{
    int i,j;
    for(i=0; i < 3; i++)
    {
        for(j=0; j<3; j++)
        {
            matrice[i][j] = -1/(11 - coeff);
        }
    }
    matrice[1][1] = (fabs(matrice[1][1]) * 8.) + 1;
    printf("centre : %.2f\n", matrice[1][1]);
}

void Convolution::buildLaplace()
{
    int i,j;
    for(i=0; i < 3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(i == 1 && j == 1) // le centre
                matrice[i][j] = 4;
            else if( ((i==1) && ( j==0 || j==2)) || ((j==1) && ( i==0 || i==2 )) ) // W, E, N, S
                matrice[i][j] = -1;
            else
                matrice[i][j] = 0;
        }
    }
}

void Convolution::buildGradient(int col0, int col1, int col2, float coeff)
{
    int i,j;
    coeff -= 21;
    coeff = fabs(coeff);
    // pour Gy
    Mx[0][0] = col0 / coeff;
    Mx[0][1] = col1 / coeff;
    Mx[0][2] = col2 / coeff;
    Mx[1][0] = 0;
    Mx[1][1] = 0;
    Mx[1][2] = 0;
    Mx[2][0] = -(col0) / coeff;
    Mx[2][1] = -(col1) / coeff;
    Mx[2][2] = -(col2) / coeff;

    for(i=0; i < 3; i++)
    {
        for(j=0; j < 3; j++)
        {
            My[i][j] = Mx[j][i];
        }
    }
}

void Convolution::buildPerso(float value[3][3])
{
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            matrice[i][j] = value[i][j];
        }
    }
}


void Convolution::calculRehausse(int x, int y, RgbImage img, RgbImage img2)
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
            resB += img2[i][j].b * matrice[i - borneMiniLig][j - borneMiniCol];
            resG += img2[i][j].g * matrice[i - borneMiniLig][j - borneMiniCol];
            resR += img2[i][j].r * matrice[i - borneMiniLig][j - borneMiniCol];
        }
    }

    // Arrondi
    resR = floor(resR + 0.5);
    resG = floor(resG + 0.5);
    resB = floor(resB + 0.5);


    // calcul du min et du max pour R
    if(resR < 0)
        resR = 0;
    else if(resR > 255)
        resR = 255;

    // calcul du min et du max pour G
    if(resG < 0)
        resG = 0;
    else if(resG > 255)
        resG = 255;

    if(resB < 0)
        resB = 0;
    else if(resB > 255)
        resB = 255;

    // Affectation dans le tableau
    img[x][y].b = resB;
    img[x][y].g = resG;
    img[x][y].r = resR;
}



void Convolution::calculGradient(int x, int y, RgbImage img, RgbImage img2)
{
    int i, j;
    int borneMiniLig, borneMiniCol, borneMaxiLig, borneMaxiCol;
    float resB = 0;
    float resG = 0;
    float resR = 0;
    float Gxb= 0;
    float Gyb = 0;
    float Gxg = 0;
    float Gyg = 0;
    float Gxr = 0;
    float Gyr = 0;

    bool boolig = false;
    bool boocol = false;
    borneMiniLig = x - rayon;
    borneMiniCol = y - rayon;
    borneMaxiLig = x + rayon;
    borneMaxiCol = y + rayon;

    // On prend les lignes de la fin
    if(borneMiniLig < 0)
    {
        borneMiniLig = 0;
        boolig = true;
    }

    if(borneMiniCol < 0)
    {
        borneMiniCol = 0;
        boocol = true;
    }

    if(borneMaxiLig >= maxlig)
    {
        borneMaxiLig = maxlig - 1;
        boolig = true;
    }

    if(borneMaxiCol >= maxcol)
    {
        borneMaxiCol = maxcol - 1;
        boocol = true;
    }

    //Coin superieur gauche
    if(x == 0 && y == 0)
    {
        for(i = borneMiniLig; i <= borneMaxiLig + 1; i++)
        {
            for(j= borneMiniCol; j <= borneMaxiCol + 1; j++)
            {
                if(i - borneMiniLig + 1 <= 2)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig + 1][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig + 1][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig + 1][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig + 1][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig + 1][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig + 1][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[0][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[0][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[0][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[0][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[0][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[0][j - borneMiniCol];
                }
                if(j - borneMiniCol + 1 <= 2)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol + 1];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol + 1];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol + 1];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol + 1];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol + 1];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol + 1];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][0];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][0];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][0];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][0];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][0];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][0];
                }

            }
        }
    }
    // coin superieur droit
    else if(x == 0 && y == maxcol - 1)
    {
        for(i = borneMiniLig; i <= borneMaxiLig + 1; i++)
        {
            for(j= borneMiniCol - 1; j <= borneMaxiCol; j++)
            {
                if(i - borneMiniLig + 1 <= 2)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig + 1][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig + 1][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig + 1][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig + 1][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig + 1][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig + 1][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[0][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[0][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[0][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[0][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[0][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[0][j - borneMiniCol];
                }

                if(j - borneMiniCol>= 0)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][2];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][2];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][2];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][2];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][2];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][2];
                }
            }
        }
    }

    // coin inferieur gauche
    else if(x == maxlig - 1 && y == 0)
    {
        for(i = borneMiniLig-1; i <= borneMaxiLig; i++)
        {
            for(j= borneMiniCol; j <= borneMaxiCol+1; j++)
            {
                if(i - borneMiniLig>= 0)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[2][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[2][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[2][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[2][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[2][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[2][j - borneMiniCol];
                }

                if(j - borneMiniCol + 1 <= 2)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol + 1];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol + 1];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol + 1];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol + 1];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol + 1];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol + 1];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][0];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][0];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][0];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][0];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][0];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][0];
                }
            }
        }
    }

    // Coin inferieur droit
    else if(x == maxlig - 1 && y == maxcol -1)
    {
        for(i = borneMiniLig-1; i <= borneMaxiLig; i++)
        {
            for(j= borneMiniCol-1; j <= borneMaxiCol; j++)
            {
                if(i - borneMiniLig>= 0)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[2][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[2][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[2][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[2][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[2][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[2][j - borneMiniCol];
                }

                if(j - borneMiniCol>= 0)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][2];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][2];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][2];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][2];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][2];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][2];
                }
            }
        }
    }

    // Premiere ligne
    else if(x == 0)
    {
        for(i = borneMiniLig; i <= borneMaxiLig+1; i++)
        {
            for(j= borneMiniCol; j <= borneMaxiCol; j++)
            {
                if(i - borneMiniLig + 1 <= 2)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig + 1][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig + 1][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig + 1][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig + 1][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig + 1][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig + 1][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[0][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[0][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[0][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[0][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[0][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[0][j - borneMiniCol];
                }

            }
        }
    }
    // Derniere ligne
    else if(x == maxlig - 1)
    {
        for(i = borneMiniLig-1; i <= borneMaxiLig; i++)
        {
            for(j= borneMiniCol; j <= borneMaxiCol; j++)
            {
                if(i - borneMiniLig>= 0)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[2][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[2][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[2][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[2][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[2][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[2][j - borneMiniCol];
                }
            }
        }
    }
    // Premiere colonne
    else if(y == 0)
    {
        for(i = borneMiniLig; i <= borneMaxiLig; i++)
        {
            for(j= borneMiniCol; j <= borneMaxiCol+1; j++)
            {
                if(j - borneMiniCol + 1 <= 2)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol + 1];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol + 1];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol + 1];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol + 1];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol + 1];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol + 1];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][0];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][0];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][0];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][0];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][0];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][0];
                }

            }
        }
    }
    // Derniere colonne
    else if(y == maxcol - 1)
    {
        for(i = borneMiniLig; i <= borneMaxiLig; i++)
        {
            for(j= borneMiniCol-1; j <= borneMaxiCol; j++)
            {
                if(j - borneMiniCol>= 0)
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][j - borneMiniCol];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];
                }
                else
                {
                    Gxb += img2[i][j].b * Mx[i - borneMiniLig][2];
                    Gxg += img2[i][j].g * Mx[i - borneMiniLig][2];
                    Gxr += img2[i][j].r * Mx[i - borneMiniLig][2];

                    Gyb += img2[i][j].b * My[i - borneMiniLig][2];
                    Gyg += img2[i][j].g * My[i - borneMiniLig][2];
                    Gyr += img2[i][j].r * My[i - borneMiniLig][2];
                }
            }
        }
    }
    // Pas d'extremite
    else
    {
        for(i = borneMiniLig; i <= borneMaxiLig; i++)
        {
            for(j= borneMiniCol; j <= borneMaxiCol; j++)
            {
                Gxb += img2[i][j].b * Mx[i - borneMiniLig][j - borneMiniCol];
                Gxg += img2[i][j].g * Mx[i - borneMiniLig][j - borneMiniCol];
                Gxr += img2[i][j].r * Mx[i - borneMiniLig][j - borneMiniCol];

                Gyb += img2[i][j].b * My[i - borneMiniLig][j - borneMiniCol];
                Gyg += img2[i][j].g * My[i - borneMiniLig ][j - borneMiniCol];
                Gyr += img2[i][j].r * My[i - borneMiniLig][j - borneMiniCol];

            }
        }
    }
    // Formule des filtres avec gradient
    resR = sqrt( (Gxr*Gxr) + (Gyr*Gyr) );
    resG = sqrt( (Gxg*Gxg) + (Gyg*Gyg) );
    resB = sqrt( (Gxb*Gxb) + (Gyb*Gyb) );

    // Arrondi
    resR = floor(resR + 0.5);
    resG = floor(resG + 0.5);
    resB = floor(resB + 0.5);

    // calcul du min et du max pour R
    if(resR < 0)
        resR = 0;
    else if(resR > 255)
        resR = 255;

    // calcul du min et du max pour G
    if(resG < 0)
        resG = 0;
    else if(resG > 255)
        resG = 255;
    if(resB < 0)
        resB = 0;
    else if(resB > 255)
        resB = 255;

    // Affectation dans le tableau
    img[x][y].b = resB;
    img[x][y].g = resG;
    img[x][y].r = resR;
}


// img = img de base
// img2 = img laplacienne
// resimg = image resultant
void Convolution::accentuation(int x, int y, RgbImage img, RgbImage img2, RgbImage resimg)
{
    int i, j;
    float resB = 0;
    float resG = 0;
    float resR = 0;

    resB = img[x][y].b - (img2[x][y].b * 0.5);
    resG = img[x][y].g - (img2[x][y].g * 0.5);
    resR = img[x][y].r - (img2[x][y].r * 0.5);
    //printf("%.1f, %.1f, %.1f\n", resB, resG, resR);


    // calcul du min et du max pour R
    if(resR < 0)
        resR = 0;
    else if(resR > 255)
        resR = 255;

    // calcul du min et du max pour G
    if(resG < 0)
        resG = 0;
    else if(resG > 255)
        resG = 255;

    if(resB < 0)
        resB = 0;
    else if(resB > 255)
        resB = 255;

    // Affectation dans le tableau
    resimg[x][y].b = resB;
    resimg[x][y].g = resG;
    resimg[x][y].r = resR;
}
