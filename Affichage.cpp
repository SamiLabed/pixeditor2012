#include "Affichage.h"
#include <iostream>
#include <stdio.h>
#include "Image.h"
#include "Flou.h"
#include <unistd.h>

Affichage::Affichage()
{
    vue = new QGraphicsView();
    position_fenetre = new QVBoxLayout(this);
    position_fenetre->addWidget(vue);

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
        int reponse = QMessageBox::question(this, "Attention", "Ce fichier existe déjà !\nVoulez-vous l'écraser ?", QMessageBox::Yes | QMessageBox::No);

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
}

void Affichage::printImag()
{
    RgbImage rgbimg(image);
    //printf("%d,%d,%d\n", rgbimg[0][0].b, rgbimg[0][0].g, rgbimg[0][0].r);

    monPixmap = QPixmap::fromImage(*image, Qt::AutoColor);
    scene->addPixmap(monPixmap);
    vue->setScene(scene);
    fichier_save = nomFichier;
    setFixedSize(image->width(),image->height());
    is_save = true;
}

void Affichage::flou()
{

}

void Affichage::histogramme()
{

}

void Affichage::quitter()
{
    if(testSauvegarde())
        qApp->quit();
}
