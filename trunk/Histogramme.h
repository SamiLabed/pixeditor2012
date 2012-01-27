#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "Image.h"
#include <QColor>
#include <QPainter>
#include <QPen>
#include <vector>
#include <algorithm>

using std::vector;

class Histogramme : public QPixmap
{

private:
    int width;
    int height;
    int x, y, i, j;
    float tmp;
    int val, maxValR, maxValG, maxValB;
    int histoR[256];
    int histoG[256];
    int histoB[256];
    int histoCumulR[256];
    int histoCumulG[256];
    int histoCumulB[256];
    int nivInitR;
    int nivInitG;
    int nivInitB;
    double *histoH;
    double *histoS;
    double *histoV;
    vector<double> vec_histoH;
    vector<double> vec_histoS;
    vector<double> vec_histoV;
    double varR, varG, varB, varH, varS, varV;
    RgbImage img;
    QColor color;
    QPainter painter;
    QPen pen;

public:
    ~Histogramme();
    Histogramme(RgbImage im, int wd, int hg);
    void calculHistoRGB();
    void calculHistoHSV();
    void rgbToHsv();
    double reduce(double var);
    void drawHistoR(QPaintDevice *dev);
    void drawHistoG(QPaintDevice *dev);
    void drawHistoB(QPaintDevice *dev);
    void drawHistoH(QPaintDevice * dev);
    void drawHistoS(QPaintDevice * dev);
    void drawHistoV(QPaintDevice * dev);
    vector<double> tabToVector(double *tab);
    int getVecHSize();
    int getVecSSize();
    int getVecVSize();
    void cumule();
    void equalize();
    void negatif();
    void seuillage(int seuil);

signals:

};

#endif // HISTOGRAMME_H
