#include "Rehaussdialog.h"
#include "Convolution.h"

RehaussDialog::RehaussDialog(Affichage* aff, RgbImage rgb)
{
    rgbbase = rgb;
    affrehauss = aff;
    grid = new QGridLayout();

    intensite = new QLabel("Intensite du rehaussement : ");

    spin = new QSpinBox();
    spin->setValue(1);
    spin->setRange(1, 10);

    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");
    QObject::connect( valider, SIGNAL(clicked()), this, SLOT(applyRehauss()) );
    QObject::connect( annuler, SIGNAL(clicked()), this, SLOT(close()) );

    grid->addWidget(intensite, 0, 0);
    grid->addWidget(spin, 0, 1);
    grid->addWidget(annuler, 1, 3);
    grid->addWidget(valider, 0, 3);

    setWindowTitle ("Rehausser l'image !");
    setLayout(grid);
    show();
}

void RehaussDialog::applyRehauss()
{
    int i,j=0;
    QImage* qtmp = new QImage(*rgbbase.imgexe);
    RgbImage tmp;
    tmp.imgexe = qtmp;

    Convolution conv(qtmp->height(), qtmp->width());
    conv.buildRehausseur((float)spin->value());

    for(i=0; i < qtmp->height(); i++)
    {
        for(j=0; j < qtmp->width(); j++)
        {
            conv.calculRehausse(i, j, rgbbase, tmp);
        }
    }
    affrehauss->refresh();
    close();
}
