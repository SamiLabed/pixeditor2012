#include "Affichage.h"
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
#include "Seamdialog.h"
#include "Seuildialog.h"

Affichage::Affichage()
{

    affichage = new AffichageLabel(this);
    position_fenetre = new QVBoxLayout(this);
    position_fenetre->addWidget(affichage);
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
        nomFichier="";
        refresh();
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
    affichage->load(rgbimg);
}

void Affichage::setRgbimg(RgbImage *rgbImg)
{
    rgbimg=*rgbImg;
}

void Affichage::setoldrgbimg(RgbImage *rgbImg)
{

    QImage *tmpImage=new QImage(image->width(), image->height(),QImage::Format_RGB32);
    rgbimgold.imgexe = tmpImage;

    int i,j=0;
    for(i=0;i<image->height();i++)
    {
        for(j=0;j<image->width();j++)
        {
            rgbimgold[i][j].b=rgbimg[i][j].b;
            rgbimgold[i][j].g=rgbimg[i][j].g;
            rgbimgold[i][j].r=rgbimg[i][j].r;
        }
    }

}

void Affichage:: precedent()
{
    if(nomFichier !=NULL || nomFichier.compare("") <0)
    {
        int i,j=0;

        if(image->height() != rgbimgold.imgexe->height())
        {

            QImage *tmpImage=new QImage(rgbimgold.imgexe->width(),
                                        rgbimgold.imgexe->height(),QImage::Format_RGB32);

            rgbimg.imgexe =tmpImage;


            for(i=0;i<tmpImage->height();i++){
                for(j=0;j<tmpImage->width();j++){
                    rgbimg[i][j].b=rgbimgold[i][j].b;
                    rgbimg[i][j].g=rgbimgold[i][j].g;
                    rgbimg[i][j].r=rgbimgold[i][j].r;
                }
            }

            tmpImage;
            printImag();

        }
        else
        {

            for(i=0;i<image->height();i++){
                for(j=0;j<image->width();j++){
                    rgbimg[i][j].b=rgbimgold[i][j].b;
                    rgbimg[i][j].g=rgbimgold[i][j].g;
                    rgbimg[i][j].r=rgbimgold[i][j].r;
                }
            }

            rgbimg.imgexe=rgbimgold.imgexe;
            image=rgbimgold.imgexe;
            printImag();

        }
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}



void Affichage::printImag()
{
    affichage->setPixmap(QPixmap::fromImage(*image));
    affichage->setFixedSize(image->width(),image->height());
    affichage->load(rgbimg);
    fichier_save = nomFichier;
    is_save = false;
}

void Affichage::refresh()
{
    affichage->setPixmap(QPixmap::fromImage(*image));
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

void Affichage::loadseam()
{
    if(nomFichier !=NULL)
    {
        new Seamdialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this,"Attention","Veuillez choisir une image !" );
    }

}

void Affichage::histogrammeRGB()
{
    h = new Histogramme(rgbimg, image->width(), image->height());
    h->calculHistoRGB();
    histoPixmap = new QPixmap(300, 400);
    h->drawHistoR(histoPixmap);
    labelR.setPixmap(*histoPixmap);
    labelR.show();

    h = new Histogramme(rgbimg, image->width(), image->height());
    h->calculHistoRGB();
    histoPixmap = new QPixmap(300, 400);
    h->drawHistoG(histoPixmap);
    labelG.setPixmap(*histoPixmap);
    labelG.show();

    h = new Histogramme(rgbimg, image->width(), image->height());
    h->calculHistoRGB();
    histoPixmap = new QPixmap(300, 400);
    h->drawHistoB(histoPixmap);
    labelB.setPixmap(*histoPixmap);
    labelB.show();
}

void Affichage::histogrammeHSV()
{
    h = new Histogramme(rgbimg, image->width(), image->height());
    h->calculHistoHSV();
    taille = h->getVecHSize();
    histoPixmap = new QPixmap(taille, 400);
    h->drawHistoH(histoPixmap);
    labelH.setPixmap(*histoPixmap);
    labelH.show();

    h = new Histogramme(rgbimg, image->width(), image->height());
    h->calculHistoHSV();
    taille = h->getVecSSize();
    histoPixmap = new QPixmap(taille, 400);
    h->drawHistoS(histoPixmap);
    labelS.setPixmap(*histoPixmap);
    labelS.show();

    h = new Histogramme(rgbimg, image->width(), image->height());
    h->calculHistoHSV();
    taille = h->getVecVSize();
    histoPixmap = new QPixmap(taille, 400);
    h->drawHistoV(histoPixmap);
    labelV.setPixmap(*histoPixmap);
    labelV.show();
}

void Affichage::equalize()
{
    h = new Histogramme(rgbimg, image->width(), image->height());
    h->equalize();

    refresh();
}

void Affichage::negatif()
{
    h = new Histogramme(rgbimg, image->width(), image->height());
    h->negatif();

    refresh();
}

void Affichage::seuillage()
{
    if (nomFichier != NULL)
    {
        setoldrgbimg(&rgbimg);
        new SeuilDialog(this, rgbimg);
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Veuillez choisir une image !");
    }
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
}


void Affichage::quitter()
{
    if(testSauvegarde())
        qApp->quit();
}
