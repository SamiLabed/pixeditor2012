#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QtGui/QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QStatusBar>
#include "Affichage.h"
//#include "Affichagelabel.h"
class AffichageLabel;

class PixEditor : public QMainWindow
{
    Q_OBJECT;
    private:
        Affichage widgetcentral;
        AffichageLabel *affichage;
        //QScrollArea *scrollArea;
        QMenuBar *barre_menu;
        QMenu *menu_fichier, *menu_outils ,*histo_menu,*color_picker,*menu_selection;
        QAction *nouveau_action, *ouvrir_action, *sauver_action, *sauversous_action, *quitter_action;
        QAction *flou_action,  *histoR_action, *histoG_action, *histoB_action,*picker_action
                ,*fusion_action,*gris_action,*selection_action,
                *rehaussement_action, *detection_action, *gradient_action
                , *perso_action, *accent_action;


    public:
        PixEditor(QWidget *parent = 0);
        ~PixEditor();
        void addMenu();
        void addStatutBar();

};

#endif // MAFENETRE_H
