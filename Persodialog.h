#ifndef PERSODIALOG_H
#define PERSODIALOG_H

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

class Persodialog : public QWidget
{
    Q_OBJECT
public:
    Persodialog(Affichage* aff, RgbImage rgb);
    QLabel *labmat1, *labmat2, *labmat3;
    QGridLayout *grid;
    QLineEdit* cases[3][3];
    QPushButton *valider;
    QPushButton *annuler;
    RgbImage rgbbase;
    Affichage* affperso;
    bool ok[3][3];


signals:

public slots:
    void applyPerso();
};

#endif // PERSODIALOG_H
