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

class WidgetPrincipal : public QWidget
{
    Q_OBJECT;
    private:
        QGraphicsScene *a_scene;
        QGraphicsView *a_paint;
        QVBoxLayout *a_positionFenetre;
        QImage *a_monImage;
        //iplImage

        bool a_isSave;
        QString a_fichierDeSauvegarde;
    public:
        WidgetPrincipal();

    public slots:
        void nouveau();
        void ouvrir();
        void sauvegarder();
        bool sauvegarderSous();
        bool testSauvegarde();
        void quitter();
        //void flou();

    signals:
        void nouvelleProgression(int);
};



#endif // WIDGETPRINCIPAL_H
