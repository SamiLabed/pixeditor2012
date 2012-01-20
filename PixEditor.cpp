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
    flou_action->setStatusTip(tr("Appliquer un flou  l'image"));
    QObject::connect(flou_action, SIGNAL(triggered()), &widgetcentral, SLOT(loadflou()));

    fusion_action = new QAction(tr("&F&usion"), this);
    fusion_action->setStatusTip(tr("Fusionner l'image avec une autre"));
    QObject::connect(fusion_action, SIGNAL(triggered()), &widgetcentral, SLOT(loadfusion()));

    gris_action = new QAction(tr("&Gris"),this);
    gris_action->setStatusTip("Appliquer un gris l'image");
    QObject::connect(gris_action,SIGNAL(triggered()),&widgetcentral,SLOT(gris()));

    rehaussement_action = new QAction(tr("&Rehaussement de contraste"),this);
    rehaussement_action->setStatusTip("Rehausser le contraste");
    QObject::connect(rehaussement_action,SIGNAL(triggered()),&widgetcentral,SLOT(loadrehausseur()));

    detection_action = new QAction(tr("&Detecter les contours"),this);
    detection_action->setStatusTip("Detection de contour");
    QObject::connect(detection_action,SIGNAL(triggered()),&widgetcentral,SLOT(loaddetection()));

    gradient_action = new QAction(tr("&Gradient"),this);
    gradient_action->setStatusTip("Gradient");
    QObject::connect(gradient_action,SIGNAL(triggered()),&widgetcentral,SLOT(loadgradient()));

    perso_action = new QAction(tr("&Personnaliser"),this);
    perso_action->setStatusTip("Personnaliser le filtre");
    QObject::connect(perso_action,SIGNAL(triggered()),&widgetcentral,SLOT(loadperso()));

    accent_action = new QAction(tr("&Accentuer"),this);
    accent_action->setStatusTip("Accentuer l'image");
    QObject::connect(accent_action,SIGNAL(triggered()),&widgetcentral,SLOT(loadaccentuer()));

    menu_outils = new QMenu(tr("F&iltre"), this);
    menu_outils->addAction(flou_action);
    menu_outils->addAction(fusion_action);
    menu_outils->addAction(gris_action);
    menu_outils->addAction(rehaussement_action);
    menu_outils->addAction(detection_action);
    menu_outils->addAction(gradient_action);
    menu_outils->addAction(perso_action);
    menu_outils->addAction(accent_action);



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


    //color_picker
    picker_action = new QAction(tr("&Picolor"),this);
    QObject::connect(picker_action, SIGNAL(triggered()), widgetcentral.affichage, SLOT(pixelcolor()));
    color_picker = new QMenu(tr("&Picolor"),this);
    color_picker->addAction(picker_action);

    //selection
    menu_selection = new QMenu(tr("&Selection"),this);
    selection_action=new QAction(tr("&selection"),this);
    QObject::connect(selection_action, SIGNAL(triggered()), &widgetcentral, SLOT(selection()));
    menu_selection->addAction(selection_action);

    barre_menu = new QMenuBar(this);
    barre_menu->addMenu(menu_fichier);
    barre_menu->addMenu(menu_outils);
    barre_menu->addMenu(histo_menu);
    barre_menu->addMenu(color_picker);
    barre_menu->addMenu(menu_selection);


    setMenuBar(barre_menu);
}

PixEditor::~PixEditor()
{

}

