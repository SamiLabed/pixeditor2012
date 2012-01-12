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
#include <QPixmap>
#include <QRgb>
#include <Floudialog.h>

class Affichage : public QWidget
{
    Q_OBJECT;
    private:
        QGraphicsScene *scene;
        QGraphicsView *vue;
        QVBoxLayout *position_fenetre;

        QPixmap monPixmap;
        bool is_save;
        QString fichier_save;
        QString nomFichier;
        FlouDialog dialogFlou;

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
        void histogramme();

    signals:
};



#endif // WIDGETPRINCIPAL_H
