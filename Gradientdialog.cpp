#include "Gradientdialog.h"
#include "Convolution.h"
GradientDialog::GradientDialog(Affichage* aff, RgbImage rgb)
{
    rgbbase = rgb;
    affgradient = aff;
    grid = new QGridLayout();

    labfiltre = new QLabel("Nom du filtre : ");
    prewitt = new QRadioButton("Prewitt");
    sobel = new QRadioButton("Sobel");
    scharr = new QRadioButton("Scharr");
    labfiltre = new QLabel("Nom du filtre : ");

    labpourcent = new QLabel("Epaisseur des contours : ");
    spin = new QSpinBox();
    spin->setValue(1);
    spin->setRange(1, 10);

    valider = new QPushButton("Appliquer");
    annuler = new QPushButton("Annuler");
    QObject::connect( valider, SIGNAL(clicked()), this, SLOT(applyGradient()) );
    QObject::connect( annuler, SIGNAL(clicked()), this, SLOT(close()) );

    grid->addWidget(labfiltre, 0, 0);
    grid->addWidget(prewitt, 0, 1);
    grid->addWidget(sobel, 0, 2);
    grid->addWidget(scharr, 0, 3);
    grid->addWidget(labpourcent, 1, 0);
    grid->addWidget(spin, 1, 1);
    grid->addWidget(annuler, 2, 2);
    grid->addWidget(valider, 2, 3);

    setWindowTitle ("Appliquer un filtre gradient !");
    setLayout(grid);
    show();
}

void GradientDialog:: applyGradient()
{
    int i,j=0;
    QImage* qtmp = new QImage(*rgbbase.imgexe);
    RgbImage tmp;
    tmp.imgexe = qtmp;

    if(prewitt->isChecked() == false && sobel->isChecked() == false && scharr->isChecked() == false)
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir un filtre !" );
    }
    else if(prewitt->isChecked() == true)
    {
        Convolution conv(qtmp->height(), qtmp->width());
        conv.buildGradient(1, 1, 1, (float)spin->value());
        for(i=0; i < qtmp->height(); i++)
        {
            for(j=0; j < qtmp->width(); j++)
            {
                conv.calculGradient(i, j, rgbbase, tmp);
            }
        }
        affgradient->refresh();
        close();
    }
    else if(sobel->isChecked() == true)
    {
        Convolution conv(qtmp->height(), qtmp->width());
        conv.buildGradient(1, 2, 1, (float)spin->value());
        for(i=0; i < qtmp->height(); i++)
        {
            for(j=0; j < qtmp->width(); j++)
            {
                conv.calculGradient(i, j, rgbbase, tmp);
            }
        }
        affgradient->refresh();
        close();
    }
    else if(scharr->isChecked() == true)
    {
        Convolution conv(qtmp->height(), qtmp->width());
        conv.buildGradient(3, 10, 3, (float)spin->value());
        for(i=0; i < qtmp->height(); i++)
        {
            for(j=0; j < qtmp->width(); j++)
            {
                conv.calculGradient(i, j, rgbbase, tmp);
            }
        }
        affgradient->refresh();
        close();
    }
}
