#ifndef GRADIENTDIALOG_H
#define GRADIENTDIALOG_H

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

class GradientDialog : public QWidget
{
    Q_OBJECT
public:
    GradientDialog(Affichage* aff, RgbImage rgb);
    QGridLayout *grid;
    QLabel *labfiltre;
    QSpinBox *spin;
    QLabel *labpourcent;
    QRadioButton* prewitt;
    QRadioButton* sobel;
    QRadioButton* scharr;
    QPushButton *valider;
    QPushButton *annuler;
    RgbImage rgbbase;
    Affichage* affgradient;


signals:

public slots:
    void applyGradient();
};

#endif // GRADIENTDIALOG_H
