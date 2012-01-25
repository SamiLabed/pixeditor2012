#include "Persodialog.h"
#include "Convolution.h"
#include <iostream>

Persodialog::Persodialog(Affichage* aff, RgbImage rgb)
{
    rgbbase = rgb;
    affperso = aff;
    int i,j;
    grid = new QGridLayout();
    labmat1 = new QLabel("Entrez les");
    labmat2 = new QLabel("valeurs de ");
    labmat3 = new QLabel("votre matrice");

    for(i=0; i < 3; i++)
    {
        for(j=0; j < 3; j++)
        {
            cases[i][j] = new QLineEdit();
            cases[i][j]->setFixedSize(30, 30);
            grid->addWidget(cases[i][j], i+1, j+1);
        }
    }

    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");
    QObject::connect( valider, SIGNAL(clicked()), this, SLOT(applyPerso()) );
    QObject::connect( annuler, SIGNAL(clicked()), this, SLOT(close()) );

    grid->addWidget(labmat1, 1, 0);
    grid->addWidget(labmat2, 2, 0);
    grid->addWidget(labmat3, 3, 0);
    grid->addWidget(annuler, 2, 4);
    grid->addWidget(valider, 1, 4);
    setLayout(grid);
    show();
}

void Persodialog::applyPerso()
{
    int i,j;
    bool verif = true;
    float valperso[3][3];

    for(i=0; i < 3; i++)
    {
        for(j=0; j < 3; j++)
        {
            if(cases[i][j]->text().toFloat(&ok[i][j]) == false)
            {
                if(cases[i][j]->text().compare("0") != 0) // prend pas le zero.
                    verif = false;
            }
            valperso[i][j] = cases[i][j]->text().toFloat();
        }
    }

    if(verif == false)
        QMessageBox::warning(this,"Attention","Veuillez entrer toutes les valeurs correctement !" );
    else
    {
        QImage* qtmp = new QImage(*rgbbase.imgexe);
        RgbImage tmp;
        tmp.imgexe = qtmp;

        Convolution conv(qtmp->height(), qtmp->width());
        conv.buildPerso(valperso);

        for(i=0; i < qtmp->height(); i++)
        {
            for(j=0; j < qtmp->width(); j++)
            {
                conv.calculRehausse(i, j, rgbbase, tmp);
            }
        }
        affperso->refresh();
        close();
    }

}
