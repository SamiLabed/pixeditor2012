#include "Floudialog.h"

FlouDialog::FlouDialog()
{

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
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(quitter()));
    layout->addWidget(valider);

    //layout->addWidget(spinBox);
    layout->addWidget(valider);
    setLayout(layout);

}

void FlouDialog::flou()
{
    show();

}


void FlouDialog::quitter()
{
    //prin->setTailleFlou(spinBox->value());
    taille = spinBox->value();
    this->setVisible(false);
    //this->close();

}
