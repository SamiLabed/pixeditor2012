#ifndef FUSIONDIALOG_H
#define FUSIONDIALOG_H

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
class Fusiondialog : public QWidget
{
    Q_OBJECT
public:
    Fusiondialog(Affichage* aff, RgbImage rgb);
    QDialogButtonBox *okannul;
    QGridLayout *grid;
    QLineEdit *texte_fichier;
    QLabel *labnom;
    QDoubleSpinBox *spin;
    QLabel *labpourcent;
    QPushButton *choisir;
    QPushButton *valider;
    QPushButton *annuler;
    QImage* imgfusion;
    RgbImage rgbbase;
    Affichage* affiche_fusion;


signals:

public slots:
    void applyfusion();
    void openfile();
};

#endif // FUSIONDIALOG_H
