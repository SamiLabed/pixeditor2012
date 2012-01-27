#include "Histogramme.h"

using std::max;
using std::min;
using std::sort;
using std::unique;

Histogramme::Histogramme(RgbImage im, int wd, int hg)
{
    img = im;
    width = wd;
    height = hg;
}

Histogramme::~Histogramme()
{
}

///////////////////////////////////////////
//      Fonction de calcul RGB           //
///////////////////////////////////////////
void Histogramme::calculHistoRGB()      /* Calcul de l'histogramme */
{
    maxValR = 0;
    maxValG = 0;
    maxValB = 0;

    for (i=0; i<256; i++)
    {
        histoR[i] = 0;
        histoG[i] = 0;
        histoB[i] = 0;
    }

    for (x=0; x<height; x++)
    {
        for (y=0; y<width; y++)
        {
            tmp = img[x][y].r;
            val = (int)tmp;
            histoR[val]++;
            if (histoR[val] > histoR[maxValR])
                maxValR = val;

            tmp = img[x][y].g;
            val = (int)tmp;
            histoG[val]++;
            if (histoG[val] > histoG[maxValG])
                maxValG = val;

            tmp = img[x][y].b;
            val = (int)tmp;
            histoB[val]++;
            if (histoB[val] > histoB[maxValB])
                maxValB = val;
        }
    }
}

///////////////////////////////////////////
//      Fonctions de calcul HSV          //
///////////////////////////////////////////

void Histogramme::calculHistoHSV()
{
    histoH = new double[width*height];
    histoS = new double[width*height];
    histoV = new double[width*height];

    for (x=0; x<height; x++)
    {
        for (y=0; y<width; y++)
        {
            varR = (img[x][y].r)/255.0;
            varG = (img[x][y].g)/255.0;
            varB = (img[x][y].b)/255.0;

            rgbToHsv();

            histoH[x*y+y] = reduce(varH);
            histoS[x*y+y] = reduce(varS);
            histoV[x*y+y] = reduce(varV);
        }
    }

    vec_histoH = tabToVector(histoH);
    vec_histoS = tabToVector(histoS);
    vec_histoV = tabToVector(histoV);

    delete [] histoH;
    delete [] histoS;
    delete [] histoV;
}

void Histogramme::rgbToHsv()
{
    double varMinTmp, varMaxTmp, varMin, varMax, deltaMax;
    double deltaR, deltaG, deltaB;

    varH = 0;
    varS = 0;
    varV = 0;

    varMinTmp = min(varR, varG);
    varMin = min(varMinTmp, varB);
    varMaxTmp = max(varR, varG);
    varMax = max(varMaxTmp, varB);
    deltaMax = varMax-varMin;

    varV = varMax;

    if (deltaMax == 0)
    {
       varH = 0;
       varS = 0;
    }
    else
    {
       varS = deltaMax/varMax;

       deltaR = (((varMax-varR)/6)+(deltaMax/2))/deltaMax;
       deltaG = (((varMax-varG)/6)+(deltaMax/2))/deltaMax;
       deltaB = (((varMax-varB)/6)+(deltaMax/2))/deltaMax;

       if      (varR == varMax) varH = deltaB-deltaG;
       else if (varG == varMax) varH = (1/3)+deltaR-deltaB;
       else if (varB == varMax) varH = (2/3)+deltaG-deltaR;

       if (varH < 0) varH += 1;
       if (varH > 1) varH -= 1;
    }
}

double Histogramme::reduce(double var)
{
    double varTmp = var*1000;
    double varTmp2 = floor(varTmp);
    var = varTmp2/1000;

    return var;
}

vector<double> Histogramme::tabToVector(double *tab)
{
    vector<double> vec;
    vector<double>::iterator vec_tri;

    sort(tab, tab+(width*height));

    for (i=0; i<width*height; i++)
    {
        vec.push_back(tab[i]);
    }

    vec_tri = unique(vec.begin(), vec.end());
    vec.resize(vec_tri - vec.begin());

    return vec;
}

///////////////////////////////////////////
//      Accesseurs                       //
///////////////////////////////////////////

int Histogramme::getVecHSize()
{
    return vec_histoH.size();
}

int Histogramme::getVecSSize()
{
    return vec_histoS.size();
}

int Histogramme::getVecVSize()
{
    return vec_histoV.size();
}

///////////////////////////////////////////
//      Fonctions de dessin              //
///////////////////////////////////////////

void Histogramme::drawHistoR(QPaintDevice * dev)
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::red);

    painter.fillRect(0, 0, 400, 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<256; x++)
    {
        painter.drawLine(x,400,x,400-histoR[x]/10);
    }

    painter.end();
}

void Histogramme::drawHistoG(QPaintDevice * dev)
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::green);

    painter.fillRect(0, 0, 400, 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<256; x++)
    {
        painter.drawLine(x,400,x,400-histoG[x]/10);
    }

    painter.end();
}

void Histogramme::drawHistoB(QPaintDevice * dev)
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::blue);

    painter.fillRect(0, 0, 400, 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<256; x++)
    {
        painter.drawLine(x,400,x,400-histoB[x]/10);
    }

    painter.end();
}

void Histogramme::drawHistoH(QPaintDevice * dev)
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::black);

    painter.fillRect(0, 0, vec_histoH.size(), 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<vec_histoH.size(); x++)
    {
        painter.drawLine(x,400,x,400-vec_histoH[x]*100);
    }

    painter.end();
}

void Histogramme::drawHistoS(QPaintDevice * dev)
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::black);

    painter.fillRect(0, 0, vec_histoS.size(), 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<vec_histoS.size(); x++)
    {
        painter.drawLine(x,400,x,400-vec_histoS[x]*100);
    }

    painter.end();
}

void Histogramme::drawHistoV(QPaintDevice * dev)
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::black);

    painter.fillRect(0, 0, vec_histoV.size(), 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<vec_histoV.size(); x++)
    {
        painter.drawLine(x,400,x,400-vec_histoV[x]*100);
    }

    painter.end();
}

///////////////////////////////////////////
//      Fonctions de modification        //
///////////////////////////////////////////

void Histogramme::cumule()
{
    int sommeR = 0;
    int sommeG = 0;
    int sommeB = 0;

    for (i=0; i<256; i++)
    {
        histoCumulR[i] = 0;
        histoCumulG[i] = 0;
        histoCumulB[i] = 0;
    }

    for (i=0; i<256; i++)
    {
        sommeR += histoR[i];
        histoCumulR[i] = sommeR;
        sommeG += histoG[i];
        histoCumulG[i] = sommeG;

        sommeB += histoB[i];
        histoCumulB[i] = sommeB;
    }
}

void Histogramme::egalisation()
{
    calculHistoRGB();
    cumule();

    nivInitR = 0;
    nivInitG = 0;
    nivInitB = 0;

    for (x=0; x<height; x++)
    {
        for (y=0; y<width; y++)
        {
            nivInitR = (int)img[x][y].r;
            nivInitG = (int)img[x][y].g;
            nivInitB = (int)img[x][y].b;

            img[x][y].r = 255*histoCumulR[nivInitR]/(width*height);
            img[x][y].g = 255*histoCumulG[nivInitG]/(width*height);
            img[x][y].b = 255*histoCumulB[nivInitB]/(width*height);
        }
    }
}

void Histogramme::linearisation()
{
    int minR = 255;
    int maxR = 0;
    int minG = 255;
    int maxG = 0;
    int minB = 255;
    int maxB = 0;

    calculHistoRGB();

    for (i=0; i<256; i++)
    {
        if (histoR[i] != 0 && i < minR) minR = i;
        if (histoR[i] != 0 && i > maxR) maxR = i;

        if (histoG[i] != 0 && i < minG) minG = i;
        if (histoG[i] != 0 && i > maxG) maxG = i;

        if (histoB[i] != 0 && i < minB) minB = i;
        if (histoB[i] != 0 && i > maxB) maxB = i;
    }

    nivInitR = 0;
    nivInitG = 0;
    nivInitB = 0;

    for (x=0; x<height; x++)
    {
        for (y=0; y<width; y++)
        {
            nivInitR = (int)img[x][y].r;
            nivInitG = (int)img[x][y].g;
            nivInitB = (int)img[x][y].b;

            img[x][y].r = 255*(nivInitR-minR)/(maxR-minR);
            img[x][y].g = 255*(nivInitG-minG)/(maxG-minG);
            img[x][y].b = 255*(nivInitB-minB)/(maxB-minB);
        }
    }
}

void Histogramme::negatif()
{
    for (x=0; x<height; x++)
    {
        for (y=0; y<width; y++)
        {
            img[x][y].r = 255-img[x][y].r;
            img[x][y].g = 255-img[x][y].g;
            img[x][y].b = 255-img[x][y].b;
        }
    }
}

void Histogramme::seuillage(int seuil)
{
    for (x=0; x<height; x++)
    {
        for (y=0; y<width; y++)
        {
            if (img[x][y].r < seuil) img[x][y].r = 0;
            else img[x][y].r = 255;

            if (img[x][y].g < seuil) img[x][y].g = 0;
            else img[x][y].g = 255;

            if (img[x][y].b < seuil) img[x][y].b = 0;
            else img[x][y].b = 255;
        }
    }
}
