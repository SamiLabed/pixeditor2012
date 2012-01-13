#include "Fusiondialog.h"
#include <stdio.h>

Fusiondialog::Fusiondialog(Affichage* aff, RgbImage rgb)
{
    imgfusion = NULL;
    rgbbase = rgb;
    affiche_fusion = aff;
    texte_fichier = new QLineEdit;
    texte_fichier->setReadOnly(true);

    spin = new QDoubleSpinBox;
    spin->setRange(0. ,100.0);
    spin->setSingleStep(1.);
    spin->setValue(0.);

    labnom = new QLabel("Nom de l'image ", this);
    labpourcent = new QLabel("Pourcentage ");
    choisir = new QPushButton("...");
    valider = new QPushButton("&Valider");
    annuler = new QPushButton("&Annuler");

    QObject::connect( choisir, SIGNAL(clicked()), this, SLOT(openfile()) );
    QObject::connect( valider, SIGNAL(clicked()), this, SLOT(applyfusion()) );
    QObject::connect( annuler, SIGNAL(clicked()), this, SLOT(close()) );


    grid = new QGridLayout;
    grid->addWidget(labnom, 0, 0);
    grid->addWidget(texte_fichier, 0, 1, 1, 2);
    grid->addWidget(choisir, 0, 3);
    grid->addWidget(labpourcent, 1, 0);
    grid->addWidget(spin, 1, 1);
    grid->addWidget(annuler, 2, 2);
    grid->addWidget(valider, 2, 3);

    setWindowTitle ("Appliquer une fusion !");
    setLayout(grid);

    show();
}

void Fusiondialog::applyfusion()
{
    if(imgfusion != NULL)
    {
        RgbImage rgbfusion(imgfusion);
        Fusion* fu = new Fusion();
        float tmpf = 0.01 * spin->value();
        fu->calculFusion(rgbbase, rgbfusion, tmpf);
        affiche_fusion->refresh();
        close();
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }
}

void Fusiondialog::openfile()
{
    QString tmp = QFileDialog::getOpenFileName(0, "Ouvrir", 0,  "Images (*.bmp .png *.gif *.jpg *.jpeg)");
    texte_fichier->setText(tmp);
    imgfusion = new QImage(tmp);
}
