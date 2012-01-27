#include "Energie.h"
#include "Gris.h"
#include "Convolution.h"

Energie::Energie(Affichage *affiche, RgbImage rgb, RgbImage rgbcolor, int mlig, int mcol, int nwlig, int nwcol)
{
    affenergie = affiche;
    rgbbase = rgb;
    maxlig = mlig;
    maxcol = mcol;
    nblig = abs(maxlig - nwlig);
    nbcol = abs(maxcol - nwcol);
    if(nwcol > mcol)
        isSuppr=false;
    else
        isSuppr=true;

    qimgOrigi = new QImage(*rgbcolor.imgexe); // image original
    imgOrigi.imgexe = qimgOrigi;
    int i;
    coordUse = new nodeUse* [mlig];
    for (i = 0; i < mlig; i++)
    {
        coordUse[i] = new nodeUse[mcol];
    }
}


bool Energie::compareVector(const chemins i, const chemins j) { return (i.cout < j.cout); }


void Energie::calcEnergy()
{
    int i,j;

    // dupliquer l'image de base pour generer l'image d'energie
    QImage* qenergy = new QImage(*rgbbase.imgexe);
    RgbImage rgbenergy;
    rgbenergy.imgexe = qenergy;

    QImage* qtmp = new QImage(*rgbenergy.imgexe);
    RgbImage tmp;
    tmp.imgexe = qtmp;

    // Application filtre Sobel
    Convolution conv(maxlig, maxcol);
    conv.buildGradient(1, 1, 1, 1);

    for(i=0; i < maxlig; i++)
    {
        for(j=0; j < maxcol; j++)
        {
            conv.calculGradient(i, j, rgbenergy, tmp);
            coordUse[i][j].x = i;
            coordUse[i][j].y = j;
            coordUse[i][j].used = false;
        }
    }

    // 1ere ligne => 1ere ligne de l'energie
    for(i=0; i < maxcol; i++)
    {
        rgbbase[0][i].b = rgbenergy[0][i].b;
        rgbbase[0][i].g = rgbenergy[0][i].g;
        rgbbase[0][i].r = rgbenergy[0][i].r;
    }

    // On calcule l'energie cumulee de l'image
    int res;
    for(i=1; i < maxlig; i++)
    {
        for(j=1; j < maxcol; j++)
        {
            res = rgbenergy[i][j].b + minPrecedent(i, j, rgbbase);
            if(res > 255)
                res = 255;
            else if(res < 0)
                res = 0;
            rgbbase[i][j].b = rgbbase[i][j].g = rgbbase[i][j].r = res;// rgbenergy[i][j].b; // res;
        }
    }

    calcChemin();
    rgbbase.imgexe=imgRetre.imgexe;

    affenergie->rgbimg = rgbbase;
    affenergie->image = rgbbase.imgexe;
    affenergie->printImag();
}


void Energie::calcChemin()
{
    chemins tmpch;
    int i,j, k;
    // On recalcule a chaque seam enleve
    for(i=0; i < nbcol; i++)
    {
        // On calcule les chemins plus courts
        for(j=0; j < maxcol; j++)
        {
            tmpch.vec.clear();
            tmpch.cout = 0;
            successeur(-1, j, rgbbase, tmpch);
            //printf("cout[%d] = %d\n", j, tmpch.cout);
            vecChemins.push_back(tmpch);
        }
        // prend la meilleure seam et la met dans le tableau de resultat
        std::sort(vecChemins.begin(), vecChemins.end(), compareVector);
        coordRes.push_back(vecChemins.at(0).vec);
        vecChemins.clear();

        for(k=0; k < maxlig; k++)
        {
            coordUse[coordRes.at(i).at(k).x][coordRes.at(i).at(k).y].used = true;
            rgbbase[coordRes.at(i).at(k).x][coordRes.at(i).at(k).y].r = 255;
        }

    }

    // Une fois tous les chemins calcules on supprime/ajoute les seams
    if(isSuppr)
        supprSeam();
    else
        ajoutSeam();
}



// Donne le successeur de plus faible cout pour un pixel x, y
void Energie::successeur(int x, int y, RgbImage img, chemins& ch)
{
    int prec1;
    int prec2;
    int prec3;
    int tmp, res;
    int decal1=0;
    int decal2=0;
    int decal3=0;
    point coord;

    if(x >= maxlig-1)
        return;

    // Si la coordonnee sur laquelle on est, est une seam, on l'ignore

    if((x!=-1) && (coordUse[x][y].used == true))
    {
        return;
    }

    if(y == 0) // on recupere que 2 predecesseurs (on est a gauche)
    {
        prec1 = 8000; // valeur volontairement grande qui ne sera pas prise en compte
        prec2 = img[x+1][y].b;
        while(coordUse[x+1][y+decal2].used == true)
        {
            decal2++;
            prec2 = img[x+1][y+decal2].b;
        }

        prec3 = img[x+1][y+1].b;
        while(coordUse[x+1][y+1+decal3].used == true)
        {
            decal3++;
            prec3 = img[x+1][y+1+decal3].b;
        }
    }
    else if(y == maxcol - 1) // idem on recup que 2 predec (on est a droite)
    {
        prec1 = img[x+1][y-1].b;
        while(coordUse[x+1][y-1+decal1].used == true)
        {
            decal1++;
            prec1 = img[x+1][y-1+decal1].b;
        }

        prec2 = img[x+1][y].b;
        while(coordUse[x+1][y+decal2].used == true)
        {
            decal2++;
            prec2 = img[x+1][y+decal2].b;
        }

        prec3 = 8000;
    }
    else
    {
        prec1 = img[x+1][y-1].b;
        while(coordUse[x+1][y-1+decal1].used == true)
        {
            decal1++;
            prec1 = img[x+1][y-1+decal1].b;
        }
        prec2 = img[x+1][y].b;
        while(coordUse[x+1][y+decal2].used == true)
        {
            decal2++;
            prec2 = img[x+1][y+decal2].b;
        }

        prec3 = img[x+1][y+1].b;
        while(coordUse[x+1][y+1+decal3].used == true)
        {
            decal3++;
            prec3 = img[x+1][y+1+decal3].b;
        }
    }

    // Puis on calcule le minimum
    tmp = std::min(prec1, prec2);
    res = std::min(tmp, prec3);

    // On stocke les coordonnes du chemin le plus court
    if(res == prec1)
    {
        coord.x = x+1;
        coord.y = y-1+decal1;

    }
    else if(res == prec2)
    {
        coord.x = x+1;
        coord.y = y+decal2;

    }
    else
    {
        coord.x = x+1;
        coord.y = y+1+decal3;
    }

    if(coord.y> maxcol)
    {
        ch.cout = 9999999;
        return;
    }

    ch.vec.push_back(coord);
    ch.cout += res;


    //printf("cout (%d, %d) = %d\n", coord.x, coord.y, ch.cout);
    successeur(coord.x, coord.y, img, ch);
}




// retourne le min(a,b,c) des 3 predecesseurs d'un pixel
int Energie::minPrecedent(int x, int y, RgbImage img)
{
    int prec1;
    int prec2;
    int prec3;
    int tmp, res;

    if(y == 0) // on recupere que 2 predecesseurs (on est a gauche)
    {
        prec1 = 8000; // valeur volontairement grande qui ne sera pas prise en compte
        prec2 = img[x-1][y].b;
        prec3 = img[x-1][y+1].b;
    }
    else if(y == maxcol - 1) // idem on recup que 2 predec (on est a droite)
    {
        prec1 = 8000; // valeur volontairement grande qui ne sera pas prise en compte
        prec2 = img[x-1][y].b;
        prec3 = img[x-1][y-1].b;
    }
    else
    {
        prec1 = img[x-1][y-1].b;
        prec2 = img[x-1][y].b;
        prec3 = img[x-1][y+1].b;
    }

    /* Puis on calcule le minimum */
    tmp = std::min(prec1, prec2);
    res = std::min(tmp, prec3);

    return res;
}


// Dans le cadre d'un agrandissment => on ajoute les seams a l'image
void Energie::ajoutSeam()
{
    int i,j, k;
    int decalage=0;
    bool isSeam = false;
    int newcol = maxcol + nbcol;
    qimgRetre = new QImage(newcol, maxlig, qimgOrigi->format());
    imgRetre.imgexe = qimgRetre;

    for(i=0; i < maxlig; i++)
    {
        decalage=0;
        k=0;
        for(j=0; j < maxcol; j++)
        {
            imgRetre[i][k].b = imgOrigi[i][j].b;
            imgRetre[i][k].g = imgOrigi[i][j].g;
            imgRetre[i][k].r = imgOrigi[i][j].r;
            k++;

            if(coordUse[i][j].used == true)
            {
                imgRetre[i][k].b = imgOrigi[i][j].b;
                imgRetre[i][k].g = imgOrigi[i][j].g;
                imgRetre[i][k].r = imgOrigi[i][j].r;
                k++;
            }

        }
    }
}

// Dans le cadre d'un retrecissement d'une image => On supprime les seams a l'image
void Energie::supprSeam()
{
    int i,j, k;
    int newcol = maxcol - nbcol;
    qimgRetre = new QImage(newcol, maxlig, qimgOrigi->format());
    imgRetre.imgexe = qimgRetre;

    for(i=0; i < maxlig; i++)
    {
        k=0;
        for(j=0; j < maxcol; j++)
        {
            if(coordUse[i][j].used == false)
            {
                imgRetre[i][k].b = imgOrigi[i][j].b;
                imgRetre[i][k].g = imgOrigi[i][j].g;
                imgRetre[i][k].r = imgOrigi[i][j].r;
                k++;
            }

        }
    }
}
