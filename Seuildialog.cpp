#include "Seuildialog.h"

SeuilDialog::SeuilDialog(Affichage *affiche, RgbImage imbase)
{
    setFixedSize(300,150);

    affiche_seuil=affiche;
    rgbbase=imbase;

    t = new QLineEdit;

    spinBox = new QSpinBox;
    spinBox->setRange(0,255);
    spinBox->setSingleStep(1);
    spinBox->setValue(0);

    formaLayout = new QFormLayout;
    formaLayout->addRow("&Taille",spinBox);

    layout = new QVBoxLayout;
    layout->addLayout(formaLayout);

    valider = new QPushButton("Valider");
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(seuillage()));
    layout->addWidget(valider);

    layout->addWidget(valider);
    setLayout(layout);
    show();

}

void SeuilDialog::seuillage()
{
    if(rgbbase.imgexe != NULL)
    {
        int imgheight=rgbbase.imgexe->height();
        int imgwidth=rgbbase.imgexe->width();

        taille = spinBox->value();
        Histogramme *h = new Histogramme(rgbbase, imgwidth, imgheight);
        //printf("taille : %d\n", t);
        h->seuillage(taille);

        affiche_seuil->refresh();
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }
    quitter();

}


void SeuilDialog::quitter()
{
    //prin->setTailleFlou(spinBox->value());
    //taille = spinBox->value();
    //this->setVisible(false);
    this->close();

}
