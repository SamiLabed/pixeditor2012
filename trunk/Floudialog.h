#ifndef FLOUDIALOG_H
#define FLOUDIALOG_H

#include <math.h>
#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QPushButton>
#include <QImage>
#include <QRgb>
#include "Image.h"
#include "Flou.h"
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include "Affichage.h"


class FlouDialog : public QWidget
{
    Q_OBJECT;
    private:

        //Flou f;
        //IplImage *imgfloat;
        int height,width;
        QPushButton *valider;
        QLineEdit *t;
        QSpinBox * spinBox;
        QVBoxLayout *layout;
        QFormLayout *formaLayout;
        RgbImage rgbbase;
        Affichage* affiche_flou;

    public:
        FlouDialog(Affichage *affiche,RgbImage imbase);
        int getTaille();
        float taille;

    public slots:
        void quitter();
        void flou();
        //void flou(IplImage *imgfloat,int h,int w);
};

#endif // FLOUDIALOG_H
