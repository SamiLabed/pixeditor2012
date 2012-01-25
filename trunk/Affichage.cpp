#include "Affichage.h"
//#include "Affichagelabel.h"
#include <iostream>
#include <stdio.h>
#include "Flou.h"
#include "Fusiondialog.h"
#include "Floudialog.h"
#include "colorpicker.h"
#include <QStylePainter>
#include "Convolution.h"
#include "Histogramme.h"
#include "Gauss.h"
#include "Gradientdialog.h"
#include "Rehaussdialog.h"
#include "Persodialog.h"
#include "Accentdialog.h"
#include "Redimension.h"


Affichage::Affichage()
{
    //imageLabel = new QLabel(this);
    affichage = new AffichageLabel(this);
    //affichage=aff;
    position_fenetre = new QVBoxLayout(this);
    position_fenetre->addWidget(affichage);

    //picolor_action=false;
    //decouper_action=false;
    //affichage->setaffichage(this);
    fichier_save = "";
    is_save = true;
    nouveau();

}

void Affichage::setimag(QImage *img)
{
    rgbimg.imgexe=img;
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
            loadImag();
            printImag();
        }
    }
}

void Affichage::loadImag()
{
    image = new QImage(nomFichier, 0);
    rgbimg.imgexe = image;
    rgbimgold.imgexe=image;
    //rgbimgold
    //affichage->rgbimg=rgbimg;
    affichage->load(rgbimg);
}

void Affichage::setRgbimg(RgbImage *rgbImg)
{
    rgbimg=*rgbImg;
}

void Affichage::setoldrgbimg(RgbImage *rgbImg)
{
    rgbimgold=*rgbImg;
    rgbimgold.imgexe=rgbImg->imgexe;
    //rgbimgold.imgexe=rgbImg.imgexe;
    imageold=rgbImg->imgexe;
}

void Affichage:: precedent()
{
    rgbimg.imgexe=rgbimgold.imgexe;
    image=rgbimgold.imgexe;
    setRgbimg(&rgbimgold);
    printImag();
}

void Affichage::printImag()
{
    affichage->setPixmap(QPixmap::fromImage(*image));
    affichage->setFixedSize(image->width(),image->height());
    //affichage->move(0,0);
    affichage->load(rgbimg);
    imageold=image;
    setoldrgbimg(&rgbimg);
    fichier_save = nomFichier;
    is_save = true;
}

void Affichage::refresh()
{
    affichage->setPixmap(QPixmap::fromImage(*image));
    //affichage->rgbimg=rgbimg;
    //setoldrgbimg(&rgbimg);
    imageold=image;
    is_save = false;
    affichage->load(rgbimg);
}




void Affichage::loadflou()
{
    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        new FlouDialog(this,rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }
}


void Affichage::loadfusion()
{

    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        new Fusiondialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}

void Affichage::gris()
{
    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        Gris* imggris = new Gris(image->height(),image->width());
        imggris->calNivGris(rgbimg);
        refresh();
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}

void Affichage::loadrehausseur()
{
    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        new RehaussDialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }


}

void Affichage::loaddetection()
{

    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);

        Gris* imggris = new Gris(image->height(),image->width());
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
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}


void Affichage:: loadgradient()
{
    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        new GradientDialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}

void Affichage::loadperso()
{
    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        new Persodialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}

void Affichage::loadaccentuer()
{
    if(nomFichier !=NULL)
    {
        setoldrgbimg(&rgbimg);
        new AccentDialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

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

void Affichage::redimension()
{

     if(nomFichier !=NULL)
    {
         setoldrgbimg(&rgbimg);
       new Redimension(this);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

    //ReDim* imgredim = new ReDim(this);



    //refresh();
}


void Affichage::quitter()
{
    if(testSauvegarde())
        qApp->quit();
}
