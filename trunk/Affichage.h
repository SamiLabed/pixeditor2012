#ifndef WIDGETPRINCIPAL_H
#define WIDGETPRINCIPAL_H

#include <math.h>
#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include <QLabel>
#include <QColorDialog>
#include "Image.h"
#include "Gris.h"
#include "Histogramme.h"




class Affichage : public QWidget
{
    Q_OBJECT;
    private:
        QGraphicsScene *scene;
        QGraphicsView *vue;
        QVBoxLayout *position_fenetre;

        QImage *image;
        QPixmap monPixmap;
        bool is_save,picolor_action,decouper_action;
        QString fichier_save;
        QString nomFichier;
        QColorDialog dialog;
        RgbImage rgbimg;

        QPixmap *histoPixmap;
        QLabel labelR;
        QLabel labelG;
        QLabel labelB;
        Histogramme *h;
        QColor color;

        int *histo;

    public:
        Affichage();
        void loadImag();
        void printImag();


    protected:
        void    mouseMoveEvent(QMouseEvent *event);
        void    mousePressEvent(QMouseEvent *event);
        void    mouseReleaseEvent(QMouseEvent *event);

    public slots:
        void nouveau();
        void ouvrir();
        void sauvegarder();
        bool sauvegarderSous();
        bool testSauvegarde();
        void quitter();
        void gris();
        void loadflou();
        void loadfusion();
        void histogrammeR();
        void histogrammeG();
        void histogrammeB();
        void pixelcolor();
        void refresh();

    signals:
};



#endif // WIDGETPRINCIPAL_H
