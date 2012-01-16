#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "Image.h"
#include <QColor>
#include <QPainter>
#include <QPen>

class Histogramme : public QPixmap
{

private:
    int width;
    int height;
    int x, y, i;
    float tmp;
    int temp, max;
    int histo[256];
    RgbImage img;
    QColor color;
    QPainter painter;
    QPen pen;

public:
    ~Histogramme();
    Histogramme(RgbImage img, int width, int height, QColor color);
    int* calculHisto(RgbImage img, int width, int height, QColor color);
    void drawHisto(QPaintDevice * dev, int valHisto[], QColor color);

signals:

};

#endif // HISTOGRAMME_H
