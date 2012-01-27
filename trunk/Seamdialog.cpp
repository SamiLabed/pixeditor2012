#include "Seamdialog.h"
#include "Energie.h"
Seamdialog::Seamdialog(Affichage* aff, RgbImage rgb)
{
    affseam = aff;
    rgbmain = rgb;

    grid = new QGridLayout();

    largeur = new QLabel("Largeur : ");
    hauteur = new QLabel("Hauteur : ");

    line_larg = new QLineEdit();
    line_larg->setFixedSize(60, 27);
    line_larg->setText(QString::number(rgbmain.imgexe->width()));
    line_haut = new QLineEdit();
    line_haut->setText(QString::number(rgbmain.imgexe->height()));
    line_haut->setFixedSize(60, 27);

    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");
    QObject::connect( valider, SIGNAL(clicked()), this, SLOT(applySeam()) );
    QObject::connect( annuler, SIGNAL(clicked()), this, SLOT(close()) );

    grid->addWidget(largeur, 0, 0);
    grid->addWidget(line_larg, 0, 1);
    grid->addWidget(hauteur, 1, 0);
    grid->addWidget(line_haut, 1, 1);
    grid->addWidget(annuler, 2, 1);
    grid->addWidget(valider, 2, 2);

    setWindowTitle ("Redimension intelligente !");
    setLayout(grid);
    show();
}
void Seamdialog::applySeam()
{
    bool larg;
    bool haut;
    if( (line_larg->text().toInt(&larg, 10) == false) && (line_haut->text().toInt(&haut, 10) == false) )
    {
            QMessageBox::warning(this,"Attention","Veuillez entrer toutes les valeurs correctement !" );
    }
    else
    {
        QImage* qtmp = new QImage(*rgbmain.imgexe);
        RgbImage tmp;
        tmp.imgexe = qtmp;
        affseam->rgbimgold = tmp;
        Gris* imggris = new Gris(rgbmain.imgexe->height() ,rgbmain.imgexe->width());
        imggris->calNivGris(rgbmain);
        Energie* e = new Energie(affseam, rgbmain, tmp, rgbmain.imgexe->height(), rgbmain.imgexe->width(),
                    line_haut->text().toInt(), line_larg->text().toInt());
        e->calcEnergy();
        close();
    }
}
