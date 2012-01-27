#ifndef ENERGIE_H
#define ENERGIE_H

#include <math.h>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDialogButtonBox>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QPushButton>
#include <QImage>
#include <QRgb>
#include "Image.h"
#include "Fusion.h"
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QRadioButton>
#include "Affichage.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>

typedef struct
{
    int x;
    int y;
} point;


typedef struct
{
    std::vector<point> vec;
    int cout;
} chemins;

typedef struct
{
    int x;
    int y;
    bool used;
} nodeUse;

class Energie : public QWidget
{
    Q_OBJECT
public:
    Energie(Affichage *affiche, RgbImage rgb, RgbImage rgbcolor, int mlig, int mcol, int nwlig, int nwcol);
    RgbImage rgbbase;
    Affichage* affenergie;
    int maxcol;
    int maxlig;
    int nblig;
    int nbcol;
    QImage * qimgOrigi;
    RgbImage imgOrigi;
    QImage* qimgRetre;
    RgbImage imgRetre;
    QImage* qimgCumul;
    RgbImage imgCumul;
    void calcEnergy();
    int minPrecedent(int x, int y, RgbImage img);
    void successeur(int x, int y, RgbImage img, chemins& ch);
    static bool compareVector(const chemins i, const chemins j);
    void calcChemin();
    void ajoutSeam();
    void supprSeam();
    std::vector<chemins> vecChemins;
    std::vector<std::vector<point> > coordRes;
    nodeUse** coordUse;
    bool isSuppr;

signals:

public slots:

};





#endif // ENERGIE_H
