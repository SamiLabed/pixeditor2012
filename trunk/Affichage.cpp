#include "Affichage.h"
#include "Image.h"
#include "Flou.h"
#include <iostream>
#include <stdio.h>
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
            // Algo ouverture
            nouveau();
            image = new QImage(fichier, 0);
            QPixmap monPixmap;

            // On regarde si le pixel possede bien les composantes (RGB) qu'on a mis precedemment.
            RgbImage rgbimg(image);

            Flou f(7, image->height(), image->width());
            int i,j;

            for(i=0; i < image->height(); i++)
            {
                for(j=0; j < image->width(); j++)
                {
                    f.calculMoy(i, j, rgbimg);
                }
            }

            monPixmap = QPixmap::fromImage(*image);
            scene->addPixmap(monPixmap);
            vue->setScene(scene);

            fichier_save = fichier;
            is_save = true;
        }
    }
}

void Affichage::quitter()
{
    if(testSauvegarde())
        qApp->quit();
}



