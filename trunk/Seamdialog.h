#ifndef SEAMDIALOG_H
#define SEAMDIALOG_H

#include <QWidget>
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
#include "Affichage.h"

class Seamdialog : public QWidget
{
    Q_OBJECT
public:
     Seamdialog(Affichage* aff, RgbImage rgb);
     Affichage* affseam;
     RgbImage rgbmain;
     QGridLayout* grid;
     QLabel *largeur;
     QLabel *hauteur;
     QLineEdit *line_larg;
     QLineEdit *line_haut;
     QPushButton *valider;
     QPushButton *annuler;

signals:

public slots:
     void applySeam();

};

#endif // SEAMDIALOG_H
