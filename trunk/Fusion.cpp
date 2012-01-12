#include "Fusion.h"
#include <stdio.h>

Fusion::Fusion(RgbImage img1, RgbImage img2)
{
    imgbase = img1;
    imgchoisi = img2;
}


void Fusion::calculFusion(float p)
{
    float pourcent1 = 1 - p; // pourcentage de l'image de base
    float pourcent2 = p; // pourcentage de l'image choisi
    int lig1, lig2 = 0;
    int col1, col2 = 0;
    int difflig, diffcol; // ecart de taille entre
    lig1 = imgbase.imgexe->height();
    lig2 = imgchoisi.imgexe->height();
    col1 = imgbase.imgexe->width();
    col2 = imgchoisi.imgexe->width();

    int i= 0;
    int j=0;

    // L'image choisi est plus petite ou de meme taille
    if( (lig1 >= lig2) && (col1 >= col2) )
    {
        printf("plus petite ! \n");
        difflig = (lig1 - lig2) / 2;
        diffcol = (col1 - col2) / 2;
        for(i=0; i < lig2; i++)
        {
            for(j=0; j < col2; j++)
            {
                imgbase[i + difflig][j + diffcol].b = ((imgbase[i + difflig][j + diffcol].b * pourcent1)
                                                       + (imgchoisi[i][j].b * pourcent2));
                imgbase[i + difflig][j + diffcol].g = ((imgbase[i + difflig][j + diffcol].g * pourcent1)
                                                       + (imgchoisi[i][j].g * pourcent2));
                imgbase[i + difflig][j + diffcol].r = ((imgbase[i + difflig][j + diffcol].r * pourcent1)
                                                       + (imgchoisi[i][j].r * pourcent2));

            }
        }
    }
    else
    {
        difflig = (lig2 - lig1) / 2;
        diffcol = (col2 - col1) / 2;
        imgbase[i][j].b = ((imgbase[i][j].b * pourcent1)
                            + (imgchoisi[i + difflig][j + diffcol].b * pourcent2));
        imgbase[i][j].g = ((imgbase[i][j].g * pourcent1)
                                               + (imgchoisi[i + difflig][j + diffcol].g * pourcent2));
        imgbase[i][j].r = ((imgbase[i][j].r * pourcent1)
                                               + (imgchoisi[i + difflig][j + diffcol].r * pourcent2));
    }

}

Fusion::~Fusion()
{
    imgchoisi = NULL; // le destructeur de QImage va etre ensuite appele.
}
