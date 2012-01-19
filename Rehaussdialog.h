#ifndef REHAUSSDIALOG_H
#define REHAUSSDIALOG_H
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

class RehaussDialog : public QWidget
{
    Q_OBJECT
public:
    RehaussDialog(Affichage* aff, RgbImage rgb);
    QGridLayout *grid;
    QLabel *intensite;
    QSpinBox *spin;
    QPushButton *valider;
    QPushButton *annuler;
    RgbImage rgbbase;
    Affichage* affrehauss;

signals:

public slots:
    void applyRehauss();
};

#endif // REHAUSSDIALOG_H
