#include "mafenetre.h"

MaFenetre::MaFenetre(QWidget *parent)
    : QMainWindow(parent)
{
    //setFixedSize(300, 275);
    //se
    addMenu();
    //addStatutBar();
    setCentralWidget(&a_WidgetCentral);

    QObject::connect(&a_WidgetCentral,
                     SIGNAL(nouvelleProgression(int)),
                     this, SLOT(updateProgressBar(int)));
}

void MaFenetre::addMenu()
{

    // Fichier
    a_nouveauAction = new QAction(tr("&Nouveau"), this);
    a_nouveauAction->setShortcut(tr("Ctrl+N"));
    a_nouveauAction->setStatusTip(tr("Nouvelle image"));
    QObject::connect(a_nouveauAction, SIGNAL(triggered()), &a_WidgetCentral, SLOT(nouveau()));

    a_ouvrirAction = new QAction(tr("&Ouvrir"), this);
    a_ouvrirAction->setShortcut(tr("Ctrl+O"));
    a_ouvrirAction->setStatusTip(tr("Charger une image"));
    QObject::connect(a_ouvrirAction, SIGNAL(triggered()), &a_WidgetCentral, SLOT(ouvrir()));

    a_sauverAction = new QAction(tr("&Sauvegarder"), this);
    a_sauverAction->setShortcut(tr("Ctrl+S"));
    a_sauverAction->setStatusTip(tr("Sauvegarder l'image"));
    QObject::connect(a_sauverAction, SIGNAL(triggered()), &a_WidgetCentral, SLOT(sauvegarder()));

    a_sauverSousAction = new QAction(tr("S&auvegarder sous..."), this);
    a_sauverSousAction->setShortcut(tr("Ctrl+Shift+S"));
    a_sauverSousAction->setStatusTip(tr("Sauvegarder l'image sous..."));
    connect(a_sauverSousAction, SIGNAL(triggered()), &a_WidgetCentral, SLOT(sauvegarderSous()));

    a_quitterAction = new QAction(tr("&Quitter"), this);
    a_quitterAction->setStatusTip(tr("Quitter le programme"));
    QObject::connect(a_quitterAction, SIGNAL(triggered()), &a_WidgetCentral, SLOT(quitter()));

    a_fichierMenu = new QMenu(tr("&Fichier"), this);
    a_fichierMenu->addAction(a_nouveauAction);
    a_fichierMenu->addAction(a_ouvrirAction);
    a_fichierMenu->addAction(a_sauverAction);
    a_fichierMenu->addAction(a_sauverSousAction);
    a_fichierMenu->addAction(a_quitterAction);

    // Filtre
    a_flouAction = new QAction(tr("&Flou"), this);
    a_flouAction->setStatusTip(tr("Appliquer un flou à l'image"));
    QObject::connect(a_flouAction, SIGNAL(triggered()), &a_WidgetCentral, SLOT(flou()));

    a_outilsMenu = new QMenu(tr("F&iltre"), this);
    a_outilsMenu->addAction(a_flouAction);

    a_menuBar = new QMenuBar(this);
    a_menuBar->addMenu(a_fichierMenu);
    a_menuBar->addMenu(a_outilsMenu);

    setMenuBar(a_menuBar);
}

MaFenetre::~MaFenetre()
{

}
