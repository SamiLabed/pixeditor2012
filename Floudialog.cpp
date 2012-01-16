#include "Floudialog.h"

FlouDialog::FlouDialog(Affichage *affiche,RgbImage imbase)
{
    setFixedSize(300,150);

    affiche_flou=affiche;
    rgbbase=imbase;

    t = new QLineEdit;

    spinBox = new QSpinBox;
    spinBox->setRange(0,20);
    spinBox->setSingleStep(1);
    spinBox->setValue(0);

    formaLayout = new QFormLayout;
    formaLayout->addRow("&Taille",spinBox);

    layout = new QVBoxLayout;
    layout->addLayout(formaLayout);

    valider = new QPushButton("valider");
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(flou()));
    layout->addWidget(valider);

    //layout->addWidget(spinBox);
    layout->addWidget(valider);
    setLayout(layout);
    show();

}

void FlouDialog::flou()
{
    if(rgbbase.imgexe != NULL)
    {
        int imgheight=rgbbase.imgexe->height();
        int imgwidth=rgbbase.imgexe->width();

        float taille = spinBox->value();
        Flou *f = new Flou(taille,imgheight,imgwidth);

        int i,j;
        for(i=0; i < imgheight; i++)
        {
            for(j=0; j < imgwidth; j++)
            {
                f->calculMoy(i,j,rgbbase);
            }
        }
        affiche_flou->refresh();

    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }
    quitter();

}


void FlouDialog::quitter()
{
    //prin->setTailleFlou(spinBox->value());
    //taille = spinBox->value();
    //this->setVisible(false);
    this->close();

}
