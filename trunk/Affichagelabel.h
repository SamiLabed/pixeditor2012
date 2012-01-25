#ifndef AFFICHAGELABEL_H
#define AFFICHAGELABEL_H

#include <QtGui>
#include <QLabel.h>
#include <QImage.h>
#include <QColorDialog>
#include <QApplication>
#include <QWidget>
#include <QRubberBand>
#include <QPoint>
#include "Image.h"
#include <math.h>

class Affichage;
class AffichageLabel : public QLabel
{
    Q_OBJECT;
    public:
        AffichageLabel(Affichage * aff);//Affichage * parent = 0, Qt::WindowFlags f = 0);
        void load(RgbImage image);
        void imgselect();
        void setaffichage(Affichage *aff);


    private:
        RgbImage rgbimg;
        bool picolor_action,decouper_action;
        QColorDialog dialog;

        bool selectionIsShown;
        QRect selectionRect;
        QPixmap pixmap;

        Affichage *affichage;
        QPoint origin;
        QPoint fin;
        QRubberBand *rubberBand;



    protected:
        //void  paintEvent(QPaintEvent *event);
        void  mouseMoveEvent(QMouseEvent *event);
        void  mousePressEvent(QMouseEvent *event);
        void  mouseReleaseEvent(QMouseEvent *event);

    public slots:
        void pixelColor();
        void selection();

};

#endif // AFFICHAGELABEL_H
