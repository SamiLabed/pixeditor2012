#include "PixEditor.h"

PixEditor::PixEditor(QWidget *parent)
    : QMainWindow(parent)
{

    addMenu();
    setCentralWidget(&widgetcentral);

}

void PixEditor::addMenu()
{

    // Fichier
    nouveau_action = new QAction(tr("&Nouveau"), this);
    nouveau_action->setShortcut(tr("Ctrl+N"));
    nouveau_action->setStatusTip(tr("Nouvelle image"));
    QObject::connect(nouveau_action, SIGNAL(triggered()), &widgetcentral, SLOT(nouveau()));

    ouvrir_action = new QAction(tr("&Ouvrir"), this);
    ouvrir_action->setShortcut(tr("Ctrl+O"));
    ouvrir_action->setStatusTip(tr("Charger une image"));
    QObject::connect(ouvrir_action, SIGNAL(triggered()), &widgetcentral, SLOT(ouvrir()));

    sauver_action = new QAction(tr("&Sauvegarder"), this);
    sauver_action->setShortcut(tr("Ctrl+S"));
    sauver_action->setStatusTip(tr("Sauvegarder l'image"));
    QObject::connect(sauver_action, SIGNAL(triggered()), &widgetcentral, SLOT(sauvegarder()));

    sauversous_action = new QAction(tr("S&auvegarder sous..."), this);
    sauversous_action->setShortcut(tr("Ctrl+Shift+S"));
    sauversous_action->setStatusTip(tr("Sauvegarder l'image sous..."));
    connect(sauversous_action, SIGNAL(triggered()), &widgetcentral, SLOT(sauvegarderSous()));

    quitter_action = new QAction(tr("&Quitter"), this);
    quitter_action->setStatusTip(tr("Quitter le programme"));
    QObject::connect(quitter_action, SIGNAL(triggered()), &widgetcentral, SLOT(quitter()));

    menu_fichier = new QMenu(tr("&Fichier"), this);
    menu_fichier->addAction(nouveau_action);
    menu_fichier->addAction(ouvrir_action);
    menu_fichier->addAction(sauver_action);
    menu_fichier->addAction(sauversous_action);
    menu_fichier->addAction(quitter_action);

    // Filtre
    flou_action = new QAction(tr("&Flou"), this);
    flou_action->setStatusTip(tr("Appliquer un flou à l'image"));
    QObject::connect(flou_action, SIGNAL(triggered()), &widgetcentral, SLOT(flou()));

    fusion_action = new QAction(tr("&F&usion"), this);
    fusion_action->setStatusTip(tr("Fusionner l'image avec une autre"));
    QObject::connect(fusion_action, SIGNAL(triggered()), &widgetcentral, SLOT(loadfusion()));

    menu_outils = new QMenu(tr("F&iltre"), this);
    menu_outils->addAction(flou_action);
    menu_outils->addAction(fusion_action);

    //histogramme
    histo_menu=new QMenu(tr("&Histogramme"),this);

    histoR_action = new QAction(tr("&Rouge"),this);
    QObject::connect(histoR_action, SIGNAL(triggered()), &widgetcentral, SLOT(histogrammeR()));
    histo_menu->addAction(histoR_action);

    histoG_action = new QAction(tr("&Vert"),this);
    QObject::connect(histoG_action, SIGNAL(triggered()), &widgetcentral, SLOT(histogrammeG()));
    histo_menu->addAction(histoG_action);

    histoB_action = new QAction(tr("&Bleu"),this);
    QObject::connect(histoB_action, SIGNAL(triggered()), &widgetcentral, SLOT(histogrammeB()));
    histo_menu->addAction(histoB_action);


    barre_menu = new QMenuBar(this);
    barre_menu->addMenu(menu_fichier);
    barre_menu->addMenu(menu_outils);
    barre_menu->addMenu(histo_menu);

    setMenuBar(barre_menu);
}

PixEditor::~PixEditor()
{

}

