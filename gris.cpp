#include "gris.h"
#include <QImage>

Gris::Gris(int ml, int mc)
{
    maxlig = ml;
    maxcol = mc;
        }

    void Gris::calNivGris(RgbImage image)
    {
    int i, j;
    float res;

        for(i =0 ; i <=maxcol ; i++)
            {
        for(j =0 ; j <=maxlig ; j++)
                {
                   res = (image[i][j].b * 0.114) + (image[i][j].g * 0.587) + (image[i][j].r * 0.299);

                   image[i][j].b = (unsigned char) res;
                   image[i][j].g = (unsigned char) res;
                   image[i][j].r = (unsigned char) res;
                }
            }

    }
