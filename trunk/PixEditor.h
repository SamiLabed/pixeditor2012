#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QtGui/QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QStatusBar>
#include <QColor>
#include "Affichage.h"

class PixEditor : public QMainWindow
{
    Q_OBJECT
    private:
        Affichage widgetcentral;
        QMenuBar *barre_menu;
        QMenu *menu_fichier, *menu_outils ,*histo_menu;
        QAction *nouveau_action, *ouvrir_action, *sauver_action, *sauversous_action, *quitter_action;
        QAction *flou_action, *histoR_action, *histoG_action, *histoB_action, *fusion_action;

    public:
        PixEditor(QWidget *parent = 0);
        ~PixEditor();
        void addMenu();
        void addStatutBar();

};

#endif // MAFENETRE_H
