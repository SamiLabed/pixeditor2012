#ifndef PIXEDITOR_H
#define PIXEDITOR_H

#include <QtGui/QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QStatusBar>
#include "Affichage.h"

class PixEditor : public QMainWindow
{
    Q_OBJECT;
    private:
        Affichage widgetcentral;
        QMenuBar *barre_menu;
        QMenu *menu_fichier, *menu_outils;
        QAction *nouveau_action, *ouvrir_action, *sauver_action, *sauversous_action, *quitter_action;
        QAction *flou_action;


    public:
        PixEditor(QWidget *parent = 0);
        ~PixEditor();
        void addMenu();
        void addStatutBar();

};

#endif // PIXEDITOR_H
