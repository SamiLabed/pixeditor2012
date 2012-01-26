#include "Gris.h"

Gris::Gris(int ml, int mc)
{
    maxlig = ml;
    maxcol = mc;
        }

    void Gris::calNivGris(RgbImage image)
    {
    int i, j;
    float res;

        for(i =0 ; i <image.imgexe->height() ; i++)
            {
        for(j =0 ; j <image.imgexe->width() ; j++)
                {
                   res = (image[i][j].b *0.2125) + (image[i][j].g * 0.7154) + (image[i][j].r * 0.0721);

                   image[i][j].b = (unsigned char) res;
                   image[i][j].g = (unsigned char) res;
                   image[i][j].r = (unsigned char) res;
                }
            }

    }

