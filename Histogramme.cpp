#include "Histogramme.h"

Histogramme::Histogramme(RgbImage im, int w, int h, QColor c)
{
    img = im;
    width = w;
    height = h;
    color = c;
}

Histogramme::~Histogramme()
{
}

int* Histogramme::calculHisto(RgbImage img, int width, int height, QColor color)      /* Calcul de l'histogramme */
{
    max = 0;

    for (i=0; i<256; i++)
    {
        histo[i] = 0;
    }

    if (color == Qt::red)
    {
        for (x=0; x<height; x++)
        {
            for (y=0; y<width; y++)
            {
                tmp = img[x][y].r;
                temp = (int)tmp;
                histo[temp]++;
                if (histo[temp] > histo[max])
                    max = temp;
            }
        }
    }
    else if (color == Qt::green)
    {
        for (x=0; x<height; x++)
        {
            for (y=0; y<width; y++)
            {
                tmp = img[x][y].g;
                temp = (int)tmp;
                histo[temp]++;
                if (histo[temp] > histo[max])
                    max = temp;
            }
        }
    }
    else if (color == Qt::blue)
    {
        for (x=0; x<height; x++)
        {
            for (y=0; y<width; y++)
            {
                tmp = img[x][y].b;
                temp = (int)tmp;
                histo[temp]++;
                if (histo[temp] > histo[max])
                    max = temp;
            }
        }
    }

    return histo;
}

void Histogramme::drawHisto(QPaintDevice * dev, int valHisto[], QColor color)    /* Dessin de l'histogramme */
{
    QPainter painter(dev);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(color);

    painter.fillRect(0, 0, 300, 400, QBrush(Qt::white));
    painter.setPen(pen);

    for (x=0; x<256; x++)
    {
        painter.drawLine(x,400,x,400-valHisto[x]/10);
    }

    painter.end();
}
