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
#include <QLabel>
#include <QPixmap>
#include <QRgb>
#include <QColor>
#include <Floudialog.h>
#include "Histogramme.h"

class Affichage : public QWidget
{
    Q_OBJECT
    private:
        QGraphicsScene *scene;
        QGraphicsView *vue;
        QVBoxLayout *position_fenetre;

        QPixmap monPixmap;
        bool is_save;
        QString fichier_save;
        QString nomFichier;
        FlouDialog dialogFlou;

        RgbImage rgbimg;

        QPixmap *histoPixmap;
        QLabel labelR;
        QLabel labelG;
        QLabel labelB;
        Histogramme *h;
        QColor color;

        int* histo;

    public:
        Affichage();
        void loadImag();
        void printImag();
        QImage *image;

    public slots:
        void nouveau();
        void ouvrir();
        void sauvegarder();
        bool sauvegarderSous();
        bool testSauvegarde();
        void quitter();
        void flou();
        void loadfusion();
        void histogrammeR();
        void histogrammeG();
        void histogrammeB();
        void refresh();

    signals:
};



#endif // WIDGETPRINCIPAL_H
