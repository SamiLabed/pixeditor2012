#ifndef AFFICHAGE_H
#define AFFICHAGE_H

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

class Affichage : public QWidget
{
    Q_OBJECT;
    private:
        QGraphicsScene *scene;
        QGraphicsView *vue;
        QVBoxLayout *position_fenetre;
        QImage *image;
        bool is_save;
        QString fichier_save;
    public:
        Affichage();

    public slots:
        void nouveau();
        void ouvrir();
        void sauvegarder();
        bool sauvegarderSous();
        bool testSauvegarde();
        void quitter();
        //void flou();

    signals:
};



#endif // AFFICHAGE_H
