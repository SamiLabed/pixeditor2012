#ifndef AFFICHAGELABEL_H
#define AFFICHAGELABEL_H

#include <QtGui>
#include <QLabel.h>
#include <QImage.h>
#include <QColorDialog>
#include <QApplication>
#include <QWidget>
#include "Image.h"
#include <math.h>
class AffichageLabel : public QLabel
{
    Q_OBJECT;
    public:
        AffichageLabel(QWidget * parent = 0, Qt::WindowFlags f = 0 );

        void load(RgbImage image);

    private:
        RgbImage rgbimg;
        bool picolor_action,decouper_action;
        QColorDialog dialog;

    protected:
        //void  paintEvent(QPaintEvent *event);
        void  mouseMoveEvent(QMouseEvent *event);
        void  mousePressEvent(QMouseEvent *event);
        void  mouseReleaseEvent(QMouseEvent *event);

    public slots:
        void pixelcolor();
        void selection();

};

#endif // AFFICHAGELABEL_H
