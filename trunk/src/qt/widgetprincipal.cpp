#include "widgetprincipal.h"

WidgetPrincipal::WidgetPrincipal()
{
    a_paint = new QGraphicsView();
    a_positionFenetre = new QVBoxLayout(this);
    a_positionFenetre->addWidget(a_paint);

    a_fichierDeSauvegarde = "";
    a_isSave = true;
    nouveau();
}

void WidgetPrincipal::nouveau()
{
     //Nouveau
    if(testSauvegarde())
    {
        a_scene = new QGraphicsScene();
        a_paint->setScene(a_scene);
        a_monImage = new QImage;

        a_fichierDeSauvegarde = "";
        a_isSave = true;
    }
}

bool WidgetPrincipal::testSauvegarde()
{
    bool succeed = true;
    int reponse = 0;
    if(!a_isSave)
    {
        reponse = QMessageBox::question(this, "Confirmation", "Voulez-vous enregistrer l'image ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reponse == QMessageBox::Yes)
            succeed = sauvegarderSous();
    }

    if(succeed and reponse != QMessageBox::Cancel)
        return true;
    return false;
}

bool WidgetPrincipal::sauvegarderSous()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer", a_fichierDeSauvegarde, "Images (*.bmp .png *.gif *.jpg *.jpeg)");

    if(fichier.isEmpty())
        return false;

    /*if(QFile::exists(fichier))
    {
        int reponse = QMessageBox::question(this, "Attention", "Ce fichier existe déjà !\nVoulez-vous l'écraser ?", QMessageBox::Yes | QMessageBox::No);

        if (reponse == QMessageBox::No)
            return false;
    }*/
    a_fichierDeSauvegarde = fichier;
    sauvegarder();

    return true;
}

void WidgetPrincipal::sauvegarder()
{
     bool reponse = true;
     if(a_fichierDeSauvegarde.isEmpty())
         reponse = sauvegarderSous();

     if(reponse == true)
     {
         // Algo saugevarde
         a_monImage->save(a_fichierDeSauvegarde);
         a_isSave = true;
     }
}

void WidgetPrincipal::ouvrir()
{
    if(testSauvegarde())
    {
        QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir", a_fichierDeSauvegarde, "Images (*.bmp .png *.gif *.jpg *.jpeg)");

        if(fichier != "")
        {
            // Algo ouverture
            nouveau();
            a_scene->addPixmap(QPixmap(fichier));
            a_paint->setScene(a_scene);
            a_monImage = new QImage(fichier);
            // convertir fichier () en char *
            a_fichierDeSauvegarde = fichier;
            a_isSave = true;
        }
    }
}

void WidgetPrincipal::quitter()
{
    if(testSauvegarde())
        qApp->quit();
}
