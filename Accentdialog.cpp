#include "Accentdialog.h"
#include "Convolution.h"
AccentDialog::AccentDialog(Affichage* aff, RgbImage rgb)
{
    rgbbase = rgb;
    affaccent = aff;
    grid = new QGridLayout();

    intensite = new QLabel("Intensite de l'accentuation : ");

    spin = new QSpinBox();
    spin->setValue(1);
    spin->setRange(1, 10);

    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");
    QObject::connect( valider, SIGNAL(clicked()), this, SLOT(applyAccent()) );
    QObject::connect( annuler, SIGNAL(clicked()), this, SLOT(close()) );

    grid->addWidget(intensite, 0, 0);
    grid->addWidget(spin, 0, 1);
    grid->addWidget(annuler, 1, 3);
    grid->addWidget(valider, 0, 3);

    setWindowTitle ("Accentuer l'image !");
    setLayout(grid);
    show();
}

void AccentDialog::applyAccent()
{
    int i,j=0;
    QImage* qtmp = new QImage(*rgbbase.imgexe);
    RgbImage tmp;
    tmp.imgexe = qtmp;

    QImage* qtmp2 = new QImage(*rgbbase.imgexe);
    RgbImage gradient;
    gradient.imgexe = qtmp2;

    Convolution conv(qtmp->height(), qtmp->width());
    conv.buildGradient(1,2,1, (float)spin->value());

    for(i=0; i < qtmp->height(); i++)
    {
        for(j=0; j < qtmp->width(); j++)
        {
            conv.calculGradient(i, j, gradient, tmp);
        }
    }

    for(i=0; i < qtmp->height(); i++)
    {
        for(j=0; j < qtmp->width(); j++)
        {
            conv.accentuation(i, j, tmp ,gradient, rgbbase);
        }
    }
    affaccent->refresh();
    close();
}
