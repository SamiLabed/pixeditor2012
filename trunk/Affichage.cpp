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

Affichage::Affichage()
{
    vue = new QGraphicsView();
    position_fenetre = new QVBoxLayout(this);
    position_fenetre->addWidget(vue);
    picolor_action=true;
    decouper_action=false;
    fichier_save = "";
    is_save = true;
    nouveau();
}

void Affichage::nouveau()
{
    if(testSauvegarde())
    {
        scene = new QGraphicsScene();
        vue->setScene(scene);
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

    /*if(QFile::exists(fichier))
    {
        int reponse = QMessageBox::question(this, "Attention", "Ce fichier existe dj !\nVoulez-vous l'craser ?", QMessageBox::Yes | QMessageBox::No);

        if (reponse == QMessageBox::No)
            return false;
    }*/
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
            // Algo ouverture
            nouveau();
            loadImag();
            printImag();
            //load
            ////image = new QImage(fichier, 0);

            //affichage
            ////QPixmap monPixmap;
            ////int i,j;
            ////std::cout<<"test\n";

            /* Exemple :
              On met le pixel au coordonnee 0,0 est a R=200, G=100, B=0
            */
            ////for(i=0; i < 1; i++)
            ////{
            ////    QRgb* rgb = (QRgb*)image->scanLine(i);
            ////    for(j=0; j < 1; j++)
            ////    {
            ////        rgb[j] = qRgb(200,100,0);
            ////    }
            ////}
            /*
              Fin exemple
              */

            //printImag
            // On regarde si le pixel possede bien les composantes (RGB) qu'on a mis precedemment.
            ////RgbImage rgbimg(*image);
            ////printf("%d,%d,%d\n", rgbimg[0][0].b, rgbimg[0][0].g, rgbimg[0][0].r);

            ////monPixmap = QPixmap::fromImage(*image, Qt::AutoColor);
            ////scene->addPixmap(monPixmap);
            ////vue->setScene(scene);
            //Fin Print

            ////fichier_save = fichier;
            ////is_save = true;

        }
    }
}

void Affichage::loadImag()
{
    image = new QImage(nomFichier, 0);
    rgbimg.imgexe = image;
}

void Affichage::printImag()
{
    //RgbImage rgbimg(image);
    //printf("%d,%d,%d\n", rgbimg[0][0].b, rgbimg[0][0].g, rgbimg[0][0].r);

    //monPixmap = QPixmap::fromImage(*image, Qt::AutoColor);
    scene->addPixmap(QPixmap::fromImage(*image));
    vue->setScene(scene);
    fichier_save = nomFichier;
    setFixedSize(image->height(),image->width());
    is_save = true;
}

void Affichage::refresh()
{
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*image));
    vue->update();
    repaint();
}




void Affichage::loadflou()
{
    new FlouDialog(this,rgbimg);
}


void Affichage::loadfusion()
{
    new Fusiondialog(this, rgbimg);
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

void Affichage::gris()
{
    Gris imggris(image->height(),image->width());
    imggris.calNivGris(rgbimg);
    refresh();
}

void Affichage::pixelcolor()
{
    //picolor_action = !picolor_action;
    if(picolor_action==true)
        dialog.open();
    //new Colorpicker(this);


}

void Affichage::mouseMoveEvent(QMouseEvent *event)
{

}

void Affichage::mousePressEvent(QMouseEvent *event)
{
    double x = event->pos().x();
    double y = event->pos().y();

    printf("%.2f,%.2f\n", x, y);
    int r = rgbimg[(int) x][(int) y].r;
    int g = rgbimg[(int) x][(int) y].g;
    int b = rgbimg[(int) x][(int) y].b;
    int alpha = rgbimg[(int) x][(int) y].alpha;

    QColor color(r, g, b, alpha);
    if(color.isValid() && picolor_action)
        dialog.setCurrentColor(color);
}

void Affichage::mouseReleaseEvent(QMouseEvent *event)
{

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
