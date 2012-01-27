#ifndef SEUILDIALOG_H
#define SEUILDIALOG_H

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
#include "Histogramme.h"
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include "Affichage.h"

class SeuilDialog : public QWidget
{
    Q_OBJECT
    private:

        //IplImage *imgfloat;
        int height, width;
        QPushButton *valider;
        QLineEdit *t;
        QSpinBox * spinBox;
        QVBoxLayout *layout;
        QFormLayout *formaLayout;
        RgbImage rgbbase;
        Affichage* affiche_seuil;

    public:
        SeuilDialog(Affichage *affiche, RgbImage imbase);
        int getTaille();
        float taille;

    public slots:
        void quitter();
        void seuillage();
};

#endif // SEUILDIALOG_H
