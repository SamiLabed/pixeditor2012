#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QtGui/QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QStatusBar>
#include "WidgetPrincipal.h"
class MaFenetre : public QMainWindow
{
    Q_OBJECT;
    private:
        WidgetPrincipal a_WidgetCentral;
        QMenuBar *a_menuBar;
        QMenu *a_fichierMenu, *a_outilsMenu;
        QAction *a_nouveauAction, *a_ouvrirAction, *a_sauverAction, *a_sauverSousAction, *a_quitterAction;
        QAction *a_flouAction;

        QStatusBar *a_statusBar;
        QProgressBar *a_progressBar;


    public:
        MaFenetre(QWidget *parent = 0);
        ~MaFenetre();
        void addMenu();
        void addStatutBar();

};

#endif // MAFENETRE_H
