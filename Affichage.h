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


//class Affichagelabel;
#include "Affichagelabel.h"



class Affichage : public QWidget
{
    Q_OBJECT;
    private:
        QGraphicsScene *scene;
        QGraphicsView *vue;
        QVBoxLayout *position_fenetre;

        QLabel *imageLabel;
        //QImage *image;
        QPixmap monPixmap;
        bool is_save;
        QString fichier_save;
        QString nomFichier;
        QColorDialog dialog;
        //RgbImage rgbimg;

        QPixmap *histoPixmap;
        QLabel labelR;
        QLabel labelG;
        QLabel labelB;
        Histogramme *h;
        QColor color;
        int *histo;

    public:
        Affichage();
        AffichageLabel *affichage;
        QImage *image;
        QImage *imageold;
        void loadImag();
        void printImag();
        void setRgbimg(RgbImage *rgbImg);
        void setLabel(AffichageLabel *monlabel);
        void setimag(QImage *img);
        void setoldrgbimg(RgbImage *rgbImg);
        RgbImage rgbimg;
        RgbImage rgbimgold;



    protected:
        //void    paintEvent(QPaintEvent *event);
        //void    mouseMoveEvent(QMouseEvent *event);
        //void    mousePressEvent(QMouseEvent *event);
        //void    mouseReleaseEvent(QMouseEvent *event);

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
        void loadrehausseur();
        void loaddetection();
        void loadgradient();
        void loadperso();
        void loadaccentuer();
        void histogrammeR();
        void histogrammeG();
        void histogrammeB();
        void refresh();
        void redimension();
        void precedent();
    signals:
};



#endif // WIDGETPRINCIPAL_H
