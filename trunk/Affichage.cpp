#include "Affichage.h"
#include <iostream>
#include <stdio.h>
#include "Flou.h"
#include "Fusiondialog.h"
#include "Floudialog.h"
#include "colorpicker.h"
#include "Convolution.h"
#include "Histogramme.h"
#include "Gauss.h"
#include "Gradientdialog.h"
#include "Rehaussdialog.h"
#include "Persodialog.h"
#include "Accentdialog.h"
#include "Affichagelabel.h"


Affichage::Affichage()
{
    affichage = new AffichageLabel(this);
    position_fenetre = new QVBoxLayout(this);
    position_fenetre->addWidget(affichage);
    //picolor_action=false;
    //decouper_action=false;
    fichier_save = "";
    is_save = true;
    nouveau();
}

void Affichage::setLabel(AffichageLabel *monlabel)
{
    affichage=monlabel;
}

void Affichage::nouveau()
{
    if(testSauvegarde())
    {
        image = new QImage;
        fichier_save = "";
        is_save = true;
    }
}

bool Affichage::testSauvegarde()
{
    bool succeed = true;
    int reponse = 0;
    if(!is_save)
    {
        reponse = QMessageBox::question(this, "Confirmation", "Voulez-vous enregistrer l'image ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reponse == QMessageBox::Yes)
            succeed = sauvegarderSous();
    }

    if(succeed and reponse != QMessageBox::Cancel)
        return true;
    return false;
}

bool Affichage::sauvegarderSous()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer", fichier_save, "Images (*.bmp .png *.gif *.jpg *.jpeg)");

    if(fichier.isEmpty())
        return false;


    fichier_save = fichier;
    sauvegarder();

    return true;
}

void Affichage::sauvegarder()
{
    bool reponse = true;
    if(fichier_save.isEmpty())
        reponse = sauvegarderSous();

    if(reponse == true)
    {
        // Algo saugevarde
        image->save(fichier_save);
        is_save = true;
    }
}

void Affichage::ouvrir()
{
    if(testSauvegarde())
    {
        QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir", fichier_save, "Images (*.bmp .png *.gif *.jpg *.jpeg)");

        if(fichier != "")
        {
            nomFichier=fichier;
            nouveau();
            loadImag();
            printImag();

        }
    }
}

void Affichage::loadImag()
{
    //image = new QImage(nomFichier, 0);
    //rgbimg.imgexe = image;
    affichage->load(rgbimg);
    image = new QImage(nomFichier, 0);
    rgbimg.imgexe = image;
    affichage->load(rgbimg);
}

void Affichage::printImag()
{
    affichage->setPixmap(QPixmap::fromImage(*image));
    this->setFixedSize(image->width(),image->height());
    affichage->setFixedSize(image->width(),image->height());
    affichage->move(0,0);
    fichier_save = nomFichier;
    is_save = true;


    //scene->addPixmap(QPixmap::fromImage(*image));
    //vue->setScene(scene);
    //fichier_save = nomFichier;
    //setFixedSize(image->height(),image->width());
    //is_save = true;
}

void Affichage::refresh()
{
    affichage->setPixmap(QPixmap::fromImage(*image));
    affichage->load(rgbimg);

    //scene->clear();
    //scene->addPixmap(QPixmap::fromImage(*image));
    //vue->update();
    //repaint();
}




void Affichage::loadflou()
{
    //new FlouDialog(this,rgbimg);

    if(image !=NULL)
    {
        new FlouDialog(this,rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }
}


void Affichage::loadfusion()
{
    new Fusiondialog(this, rgbimg);
}

void Affichage::gris()
{
    Gris* imggris = new Gris(image->height(),image->width());
    imggris->calNivGris(rgbimg);
    refresh();
}

void Affichage::loadrehausseur()
{
    new RehaussDialog(this, rgbimg);
}

void Affichage::loaddetection()
{
    int i,j=0;
    QImage* qtmp = new QImage(*rgbimg.imgexe);
    RgbImage tmp;
    tmp.imgexe = qtmp;

    Convolution conv(image->height(), image->width());
    conv.buildLaplace();

    for(i=0; i < image->height(); i++)
    {
        for(j=0; j < image->width(); j++)
        {
            conv.calculRehausse(i, j, rgbimg, tmp);

        }
    }

    refresh();
}

void Affichage:: loadgradient()
{
    new GradientDialog(this, rgbimg);
}

void Affichage::loadperso()
{
    new Persodialog(this, rgbimg);
}

void Affichage::loadaccentuer()
{
    new AccentDialog(this, rgbimg);
}

void Affichage::histogrammeR()
{
    color = Qt::red;
    h = new Histogramme(rgbimg, image->width(), image->height(), color);
    histoPixmap = new QPixmap(300,400);
    histo = h->calculHisto(rgbimg, image->width(), image->height(), color);
    h->drawHisto(histoPixmap, histo, color);
    labelR.setPixmap(*histoPixmap);
    labelR.show();
}

void Affichage::histogrammeG()
{
    color = Qt::green;
    h = new Histogramme(rgbimg, image->width(), image->height(), color);
    histoPixmap = new QPixmap(300,400);
    histo = h->calculHisto(rgbimg, image->width(), image->height(), color);
    h->drawHisto(histoPixmap, histo, color);
    labelG.setPixmap(*histoPixmap);
    labelG.show();
}

void Affichage::histogrammeB()
{
    color = Qt::blue;
    h = new Histogramme(rgbimg, image->width(), image->height(), color);
    histoPixmap = new QPixmap(300,400);
    histo = h->calculHisto(rgbimg, image->width(), image->height(), color);
    h->drawHisto(histoPixmap, histo, color);
    labelB.setPixmap(*histoPixmap);
    labelB.show();
}

void Affichage::quitter()
{
    if(testSauvegarde())
        qApp->quit();
}
