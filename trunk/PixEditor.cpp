#include "PixEditor.h"

PixEditor::PixEditor(QWidget *parent)
    : QMainWindow(parent)
{
    barreEtat=statusBar();
    addMenu();
    addock();
    addtoolbar();

    QScrollArea *defilement = new QScrollArea();
    defilement->setMinimumSize(QSize(500,500));
    setCentralWidget(defilement);
    defilement->setWidget(&widgetcentral);
    defilement->setWidgetResizable(true);



}

void PixEditor::addock()
{
    QWidget *contenuDock = new QWidget;
    dock= new QDockWidget("Palette",this);
    dock->setWidget(contenuDock);
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    QPushButton *selection = new QPushButton("Selection");
    QPushButton *gris = new QPushButton("Gris");
    QPushButton *flou = new QPushButton("Flou");
    QPushButton *contour = new QPushButton("Contour");
    QPushButton *fusion = new QPushButton("Fusion");
    QPushButton *contraste = new QPushButton("Contraste");
    QPushButton *gradient = new QPushButton("Gradient");
    QPushButton *personaliser = new QPushButton("Personaliser");
    QPushButton *accentuer = new QPushButton("Accentuer");
    QPushButton *pixelColor = new QPushButton("PixelColor");


    connect(selection,SIGNAL(clicked()),widgetcentral.affichage, SLOT(selection()));
    connect(gris,SIGNAL(clicked()),&widgetcentral, SLOT(gris()));
    connect(flou,SIGNAL(clicked()),&widgetcentral, SLOT(loadflou()));
    connect(contour,SIGNAL(clicked()),&widgetcentral, SLOT(loaddetection()));
    connect(fusion,SIGNAL(clicked()),&widgetcentral, SLOT(loadfusion()));
    connect(contraste,SIGNAL(clicked()),&widgetcentral, SLOT(loadrehausseur()));
    connect(gradient,SIGNAL(clicked()),&widgetcentral, SLOT(loadgradient()));
    connect(personaliser,SIGNAL(clicked()),&widgetcentral, SLOT(loadperso()));
    connect(accentuer,SIGNAL(clicked()),&widgetcentral, SLOT(loadaccentuer()));
    connect(pixelColor,SIGNAL(clicked()),widgetcentral.affichage, SLOT(pixelColor()));



    QVBoxLayout *dockLayout = new QVBoxLayout;
    dockLayout->addWidget(selection);
    dockLayout->addWidget(gris);
    dockLayout->addWidget(flou);
    dockLayout->addWidget(contour);
    dockLayout->addWidget(fusion);
    dockLayout->addWidget(contraste);
    dockLayout->addWidget(gradient);
    dockLayout->addWidget(personaliser);
    dockLayout->addWidget(accentuer);
    dockLayout->addWidget(pixelColor);

    contenuDock->setLayout(dockLayout);
}

void PixEditor::addtoolbar()
{

    toolBarFichier = this->addToolBar(tr("Fichier"));
    toolBarFichier->addAction(precedent_action);
    toolBarFichier->addSeparator();
    toolBarFichier->addAction(quitter_action);
    toolBarFichier->addSeparator();
    toolBarFichier->addAction(ouvrir_action);
    toolBarFichier->addSeparator();
    toolBarFichier->addAction(sauversous_action);
    toolBarFichier->addSeparator();
    toolBarFichier->addAction(sauver_action);
    toolBarFichier->addSeparator();
    toolBarFichier->addAction(picker_action);
}

void PixEditor::addMenu()
{
    //Fichier
    precedent_action=new QAction(tr("&Precedent"),this);
    precedent_action->setIcon(QIcon("../precedent.jpg"));
    precedent_action->setStatusTip(tr("Precedent"));
    QObject::connect(precedent_action,SIGNAL(triggered()),&widgetcentral,SLOT(precedent()));

    //
    nouveau_action = new QAction(tr("&Nouveau"), this);
    nouveau_action->setIcon(QIcon("../window-new-3.png"));
    nouveau_action->setShortcut(tr("Ctrl+N"));
    nouveau_action->setStatusTip(tr("Nouvelle image"));
    QObject::connect(nouveau_action, SIGNAL(triggered()), &widgetcentral, SLOT(nouveau()));

    ouvrir_action = new QAction(tr("&Ouvrir"), this);
    ouvrir_action->setShortcut(tr("Ctrl+O"));
    ouvrir_action->setIcon(QIcon("../OpenButton.png"));
    ouvrir_action->setStatusTip(tr("Charger une image"));
    QObject::connect(ouvrir_action, SIGNAL(triggered()), &widgetcentral, SLOT(ouvrir()));

    sauver_action = new QAction(tr("&Sauvegarder"), this);
    sauver_action->setShortcut(tr("Ctrl+S"));
    sauver_action->setIcon(QIcon("../enregistrer.png"));
    sauver_action->setStatusTip(tr("Sauvegarder l'image"));
    QObject::connect(sauver_action, SIGNAL(triggered()), &widgetcentral, SLOT(sauvegarder()));

    sauversous_action = new QAction(tr("S&auvegarder sous..."), this);
    sauversous_action->setShortcut(tr("Ctrl+Shift+S"));
    sauversous_action->setIcon(QIcon("../enregistrer-sous.png"));
    sauversous_action->setStatusTip(tr("Sauvegarder l'image sous..."));
    connect(sauversous_action, SIGNAL(triggered()), &widgetcentral, SLOT(sauvegarderSous()));

    quitter_action = new QAction(tr("&Quitter"), this);
    quitter_action->setStatusTip(tr("Quitter le programme"));
    quitter_action->setIcon(QIcon("../icone-infos.png"));
    QObject::connect(quitter_action, SIGNAL(triggered()), &widgetcentral, SLOT(quitter()));

    menu_fichier = new QMenu(tr("&Fichier"), this);
    menu_fichier->addAction(precedent_action);
    menu_fichier->addAction(nouveau_action);
    menu_fichier->addAction(ouvrir_action);
    menu_fichier->addAction(sauver_action);
    menu_fichier->addAction(sauversous_action);
    menu_fichier->addAction(quitter_action);

    // Filtre
    flou_action = new QAction(tr("&F&lou"), this);
    flou_action->setStatusTip(tr("Appliquer un flou � l'image"));
    flou_action->setIcon(QIcon("../flou.gif"));
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

    menu_outils = new QMenu(tr("&F&iltre"), this);
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

    histoRGB_action = new QAction(tr("&RGB"),this);
    QObject::connect(histoRGB_action, SIGNAL(triggered()), &widgetcentral, SLOT(histogrammeRGB()));
    histo_menu->addAction(histoRGB_action);

    histoHSV_action = new QAction(tr("&HSV"),this);
    QObject::connect(histoHSV_action, SIGNAL(triggered()), &widgetcentral, SLOT(histogrammeHSV()));
    histo_menu->addAction(histoHSV_action);

    equalize_action = new QAction(tr("&Egalis�"),this);
    QObject::connect(equalize_action, SIGNAL(triggered()), &widgetcentral, SLOT(equalize()));
    histo_menu->addAction(equalize_action);

    negatif_action = new QAction(tr("&N�gatif"),this);
    QObject::connect(negatif_action, SIGNAL(triggered()), &widgetcentral, SLOT(negatif()));
    histo_menu->addAction(negatif_action);

    seuillage_action = new QAction(tr("&Seuillage"),this);
    QObject::connect(seuillage_action, SIGNAL(triggered()), &widgetcentral, SLOT(seuillage()));
    histo_menu->addAction(seuillage_action);

    //color_picker
    picker_action = new QAction(tr("&P&i&xelColor"),this);
    picker_action->setStatusTip("Pixel valeur");
    picker_action->setIcon(QIcon("../pixelcolor.jpg"));
    QObject::connect(picker_action, SIGNAL(triggered()), widgetcentral.affichage, SLOT(pixelColor()));
    color_picker = new QMenu(tr("&Picolor"),this);
    color_picker->addAction(picker_action);

    //Selection
    menu_selection = new QMenu(tr("&Se&lection"),this);
    selection_action=new QAction(tr("&selection"),this);
    QObject::connect(selection_action, SIGNAL(triggered()), widgetcentral.affichage, SLOT(selection()));
    menu_selection->addAction(selection_action);

    //redimension

    redim_action = new QAction(tr("&R&eDimension"),this);
    redim_action->setStatusTip("Appliquer le redimensionnement � l'image");
    QObject::connect(redim_action,SIGNAL(triggered()),&widgetcentral,SLOT(redimension()));

    menu_redimension = new QMenu (tr ("&R&e&dimension"), this);
    menu_redimension->addAction(redim_action);

    barre_menu = new QMenuBar(this);
    barre_menu->addMenu(menu_fichier);
    barre_menu->addMenu(menu_outils);
    barre_menu->addMenu(histo_menu);
    barre_menu->addMenu(color_picker);
    barre_menu->addMenu(menu_selection);
    barre_menu->addMenu(menu_redimension);

    setMenuBar(barre_menu);
}

PixEditor::~PixEditor()
{

}
