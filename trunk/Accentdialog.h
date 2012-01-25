#ifndef ACCENTDIALOG_H
#define ACCENTDIALOG_H

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

class AccentDialog : public QWidget
{
    Q_OBJECT
public:
    AccentDialog(Affichage* aff, RgbImage rgb);
    QGridLayout *grid;
    QLabel *intensite;
    QSpinBox *spin;
    QPushButton *valider;
    QPushButton *annuler;
    RgbImage rgbbase;
    Affichage* affaccent;
signals:

public slots:
    void applyAccent();
};

#endif // ACCENTDIALOG_H
