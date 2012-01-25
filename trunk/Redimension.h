#ifndef REDIMENSION_H
#define REDIMENSION_H

#include <QtGui/QMainWindow>
#include <QImage>
#include <QPushButton>
#include <QDialog>

class Affichage;

class Redimension : public QWidget
{
    Q_OBJECT
    public:
        QString filename;
        QString methode;
     //QPushButton *bouton1;
        QPushButton *bouton2;
        QPushButton *bouton3;
        QImage *img_sortie;
        QDialog secondfenetre;
    //QImage *image;



        int dim;
        private:
            Affichage *affichage;

    public:
        Redimension(Affichage *aff);
        ~Redimension();
        int arond(double);
        double min(double,double);
        QImage* redimension(double,QString);
        double c0(double);
        double c1(double);
        double c2(double);
        double c3(double);
        double Hr(QImage *,int,int,double);
        double Hg(QImage *,int,int,double);
        double Hb(QImage *,int,int,double);




    private slots:
        //void bouton1clicked();
        void bouton2clicked();
        void bouton3clicked();

};

#endif // REDIMENSION_H
