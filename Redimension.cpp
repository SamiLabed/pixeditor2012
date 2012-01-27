#include "Redimension.h"
#include <qmath.h>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QObject>
#include <QGroupBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QtGui>
#include "Affichage.h"

Redimension::Redimension(Affichage *aff)

{
    affichage=aff;
    //aff
    //aff


    //bouton1=new QPushButton("ouvrir");
    bouton2=new QPushButton("redimensioner");
    bouton3=new QPushButton("dimension");

    QFrame *fram=new QFrame(this);
    fram->setFrameShape(QFrame::StyledPanel);
    fram->setGeometry(0,0,400,50);

    QHBoxLayout *layout1=new QHBoxLayout;

    //layout1->addWidget(bouton1);
    layout1->addWidget(bouton2);
    layout1->addWidget(bouton3);
    fram->setLayout(layout1);

    bouton2->setEnabled(true);
    bouton3->setEnabled(false);

    //connect(bouton1,SIGNAL(clicked()),this,SLOT(bouton1clicked()));
    connect(bouton2,SIGNAL(clicked()),this,SLOT(bouton2clicked()));
    connect(bouton3,SIGNAL(clicked()),this,SLOT(bouton3clicked()));

    resize(400,50);
    show();
}


Redimension::~Redimension()
{
}

/*void Redimension::bouton1clicked()
{
    filename=QFileDialog::getOpenFileName(this,tr("Open Document"),QDir::currentPath());
    if(!filename.isEmpty())
    bouton2->setEnabled(true);

}*/

void Redimension::bouton2clicked()
{
    bool ok;
    QStringList items;
    items << tr("Au plus proche 'Standard'") << tr("Bilinear") << tr("Bicubic");
    methode = QInputDialog::getItem(this,tr("choix"),tr("méthode d'interpolation:"),items,0,false,&ok );
    if(ok)
    {
        methode=methode;
        bouton2->setEnabled(false);
        bouton3->setEnabled(true);
    }
    else
        methode="Au plus proche 'Standard'";

}

void Redimension::bouton3clicked()
{
    bool ok;
    dim=QInputDialog::getInteger(this,tr("choix de dimension"),tr("taille de sortie en %"),0,10,1000,1,&ok);
    QPixmap monPixmap;
    QImage *img_sortie;

    RgbImage tmp;
    tmp.imgexe =img_sortie;

    if(ok)
    {dim=dim;}

    else
    { dim=100;}

    ////img_sortie=redimension(double(dim)/100,methode);
    tmp.imgexe=redimension(double(dim)/100,methode);
    //affichage->rgbimg.imgexe=img_sortie;
    ////affichage->image=img_sortie;
    ////affichage->printImag();

    affichage->rgbimg.imgexe=tmp.imgexe;
    affichage->image=tmp.imgexe;
    //affichage->setimag(tmp.imgexe);
    affichage->setRgbimg(&tmp);
    affichage->printImag();

    QVBoxLayout *layout=new QVBoxLayout;


    //QLabel label;
    //monPixmap=QPixmap::fromImage(img_sortie);
    //label.setPixmap(monPixmap);
    //layout->addWidget(&label);

    //secondfenetre.setLayout(layout);
    //secondfenetre.setModal(true);
    //secondfenetre.exec();


    bouton3->setEnabled(false);
    bouton2->setEnabled(false);
    //bouton1->setEnabled(false);
    this->close();

}


//------------------------------------------------------------------------

int Redimension:: arond(double x)
{

    int y;

    if(x-floor(x)<0.5)
    {y=floor(x);
    }
    else if(x-floor(x)==0)
    { y=x;
    }
    else
    {y=x+1;
    }
    return y;
}

//------------------------------------------------------------------------

double Redimension:: min(double x,double y)
{
    if(x>y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

//------------------------------------------------------------------------
//paramètre pour la méthode des splines

double Redimension:: c0(double t){
    float a=-0.01;
    return (-a*t*t*t+a*t*t);
}

double Redimension:: c1(double t){
    float a=-0.01;
    return (-(a+2)*t*t*t+(2*a+3)*t*t-a*t);
}

double Redimension:: c2(double t){
    float a=-0.01;
    return ((a+2)*t*t*t-(a+3)*t*t+1);
}

double Redimension:: c3(double t){
    float a=-0.01;
    return (a*t*t*t-2*a*t*t+a*t);
}


double Redimension:: Hr(QImage *ime,int i,int j,double x){

    return (qRed(ime->pixel(j,i-1))*c3(x-i)+qRed(ime->pixel(j,i))*c2(x-i)+qRed(ime->pixel(j,i+1))*c1(x-i)+qRed(ime->pixel(j,i+2))*c0(x-i));
}
double Redimension:: Hg(QImage *ime,int i,int j,double x){

    return (qGreen(ime->pixel(j,i-1))*c3(x-i)+qGreen(ime->pixel(j,i))*c2(x-i)+qGreen(ime->pixel(j,i+1))*c1(x-i)+qGreen(ime->pixel(j,i+2))*c0(x-i));
}

double Redimension:: Hb(QImage *ime,int i,int j,double x){

    return (qBlue(ime->pixel(j,i-1))*c3(x-i)+qBlue(ime->pixel(j,i))*c2(x-i)+qBlue(ime->pixel(j,i+1))*c1(x-i)+qBlue(ime->pixel(j,i+2))*c0(x-i));
}




//la fonction redimensionnement
QImage* Redimension:: redimension(double n,QString methode)
{
    //bloc des declarations

    double x,xr,y,yr,dx[4],dy[4],xi[4],yi[4],p[4],s;
    int val2,val3,val1;
    QRgb val;
    /*
    QPixmap *pixmap_img = new QPixmap(file_name);
    QImage img_entree;
    img_entree=pixmap_img->toImage();*/
    QImage *img_entree =  affichage ->rgbimg.imgexe ;

    int ce=img_entree->width();
    int le=img_entree->height();
    int ls,cs;
    cs=n*ce; // ligne de sorties
    ls=n*le; // ligne d'entree
    QImage *img_sortie = new QImage(cs,ls,img_entree->format());

    //si on choisit la méthode Au plus proche 'Standard'

    if(methode=="Au plus proche 'Standard'")
    {


        //debut de la méthode du plus proche element appellée redimensionnement Au plus proche 'Standard'

        for(int i=0;i<ls;i++)
        {
            for(int j=0;j<cs;j++)
            {
                x=i*double(le)/(ls);
                y=j*double(ce)/(cs);

                x=arond(x);
                y=arond(y);

                x=(int)min(x,le-1);
                y=(int)min(y,ce-1);

                val=img_entree->pixel(y,x);

                img_sortie->setPixel(j,i,val);

            }
        }


    }

    //si on choisit la méthode bilineaire

    if(methode=="Bilinear")
    {

        //si l'image est en niveaux de gris on tient compte que d'une composante ici rouge

        if(img_entree->isGrayscale()==true)
        {
            for(int i=0;i<ls;i++)
            {
                for(int j=0;j<cs;j++)
                {
                    x=i*double(le)/ls;
                    y=j*double(ce)/cs;

                    x=min(x,le-1);
                    y=min(y,ce-1);

                    xr=x;                             // coordonnées réelles
                    yr=y;

                    x=arond(x);
                    y=arond(y);                       // calcul de l'element le plus proche


                    // on tombe exactement sur un pixel existant

                    if((xr==x)&&(yr==y))
                    {
                        img_sortie->setPixel(j,i,img_entree->pixel(y,x));
                    }

                    else
                    {
                        dx[0]=xr-x;              xi[0]=x;
                        dy[0]=yr-y;              yi[0]=y;

                        dx[1]=xr-xi[1];          xi[1]=xi[0];
                        dy[1]=yr-yi[1];          yi[1]=yi[0]+1;

                        dx[2]=xr-xi[2];          xi[2]=xi[0]+1;
                        dy[2]=yr-yi[2];          yi[2]=yi[0];

                        dx[3]=xr-xi[3];          xi[3]=xi[0]+1;
                        dy[3]=yr-yi[3];          yi[3]=yi[0]+1;



                        if(dy[0]==0)
                        {
                            p[0]=1/sqrt(dx[0]*dx[0]+dy[0]*dy[0]);
                            p[2]=1/sqrt(dx[2]*dx[2]+dy[2]*dy[2]);
                            p[3]=0;
                            p[1]=0;
                            s=p[0]+p[1]+p[2]+p[3];
                            val1=(p[0]*qRed(img_entree->pixel(yi[0],xi[0]))+p[1]*qRed(img_entree->pixel(yi[1],xi[1]))+p[2]*qRed(img_entree->pixel(yi[2],xi[2]))+p[3]*qRed(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val=qRgb(val1,val1,val1);
                            img_sortie->setPixel(j,i,val);
                        }
                        else if(dx[0]==0)
                        {
                            p[0]=1/sqrt(dx[0]*dx[0]+dy[0]*dy[0]);
                            p[1]=1/sqrt(dx[1]*dx[1]+dy[1]*dy[1]);
                            p[2]=0;
                            p[3]=0;
                            s=p[0]+p[1]+p[2]+p[3];
                            val1=(p[0]*qRed(img_entree->pixel(yi[0],xi[0]))+p[1]*qRed(img_entree->pixel(yi[1],xi[1]))+p[2]*qRed(img_entree->pixel(yi[2],xi[2]))+p[3]*qRed(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val=qRgb(val1,val1,val1);
                            img_sortie->setPixel(j,i,val);
                        }

                        else
                        {
                            p[0]=1/sqrt(dx[0]*dx[0]+dy[0]*dy[0]);
                            p[1]=1/sqrt(dx[1]*dx[1]+dy[1]*dy[1]);
                            p[2]=1/sqrt(dx[2]*dx[2]+dy[2]*dy[2]);
                            p[3]=1/sqrt(dx[3]*dx[3]+dy[3]*dy[3]);
                            s=p[0]+p[1]+p[2]+p[3];
                            s=p[0]+p[1]+p[2]+p[3];
                            val1=(p[0]*qRed(img_entree->pixel(yi[0],xi[0]))+p[1]*qRed(img_entree->pixel(yi[1],xi[1]))+p[2]*qRed(img_entree->pixel(yi[2],xi[2]))+p[3]*qRed(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val=qRgb(val1,val1,val1);
                            img_sortie->setPixel(j,i,val);
                        }

                    }
                }
            }
        }


        //si l'image est en couleur

        else
        {

            for(int i=0;i<ls;i++)
            {
                for(int j=0;j<cs;j++)
                {
                    x=i*double(le)/ls;
                    y=j*double(ce)/cs;

                    x=min(x,le-1);
                    y=min(y,ce-1);

                    xr=x;                             // coordonnées réelles
                    yr=y;

                    x=arond(x);
                    y=arond(y);                       // 1)calcul de l'element le plus proche


                    // on tombe exactement sur un pixel existant
                    if((xr==x)&&(yr==y))
                    {
                        img_sortie->setPixel(j,i,img_entree->pixel(y,x));
                    }

                    else
                    {
                        dx[0]=xr-x;              xi[0]=x;
                        dy[0]=yr-y;              yi[0]=y;

                        dx[1]=xr-xi[1];          xi[1]=xi[0];
                        dy[1]=yr-yi[1];          yi[1]=yi[0]+1;

                        dx[2]=xr-xi[2];          xi[2]=xi[0]+1;
                        dy[2]=yr-yi[2];          yi[2]=yi[0];

                        dx[3]=xr-xi[3];          xi[3]=xi[0]+1;
                        dy[3]=yr-yi[3];          yi[3]=yi[0]+1;



                        if(dx[0]==0)
                        {
                            p[0]=1/sqrt(dx[0]*dx[0]+dy[0]*dy[0]);
                            p[1]=1/sqrt(dx[1]*dx[1]+dy[1]*dy[1]);
                            p[3]=0;
                            p[2]=0;
                            s=p[0]+p[1]+p[2]+p[3];
                            val1=(p[0]*qRed(img_entree->pixel(yi[0],xi[0]))+p[1]*qRed(img_entree->pixel(yi[1],xi[1]))+p[2]*qRed(img_entree->pixel(yi[2],xi[2]))+p[3]*qRed(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val2=(p[0]*qBlue(img_entree->pixel(yi[0],xi[0]))+p[1]*qBlue(img_entree->pixel(yi[1],xi[1]))+p[2]*qBlue(img_entree->pixel(yi[2],xi[2]))+p[3]*qBlue(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val3=(p[0]*qGreen(img_entree->pixel(yi[0],xi[0]))+p[1]*qGreen(img_entree->pixel(yi[1],xi[1]))+p[2]*qGreen(img_entree->pixel(yi[2],xi[2]))+p[3]*qGreen(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val=qRgb(val1,val3,val2);
                            img_sortie->setPixel(j,i,val);
                        }
                        else if(dy[0]==0)
                        {
                            p[0]=1/sqrt(dx[0]*dx[0]+dy[0]*dy[0]);
                            p[2]=1/sqrt(dx[1]*dx[1]+dy[1]*dy[1]);
                            p[1]=0;
                            p[3]=0;
                            s=p[0]+p[1]+p[2]+p[3];

                            val1=(p[0]*qRed(img_entree->pixel(yi[0],xi[0]))+p[1]*qRed(img_entree->pixel(yi[1],xi[1]))+p[2]*qRed(img_entree->pixel(yi[2],xi[2]))+p[3]*qRed(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val2=(p[0]*qBlue(img_entree->pixel(yi[0],xi[0]))+p[1]*qBlue(img_entree->pixel(yi[1],xi[1]))+p[2]*qBlue(img_entree->pixel(yi[2],xi[2]))+p[3]*qBlue(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val3=(p[0]*qGreen(img_entree->pixel(yi[0],xi[0]))+p[1]*qGreen(img_entree->pixel(yi[1],xi[1]))+p[2]*qGreen(img_entree->pixel(yi[2],xi[2]))+p[3]*qGreen(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val=qRgb(val1,val3,val2);
                            img_sortie->setPixel(j,i,val);
                        }

                        else
                        {
                            p[0]=1/sqrt(dx[0]*dx[0]+dy[0]*dy[0]);
                            p[1]=1/sqrt(dx[1]*dx[1]+dy[1]*dy[1]);
                            p[2]=1/sqrt(dx[2]*dx[2]+dy[2]*dy[2]);
                            p[3]=1/sqrt(dx[3]*dx[3]+dy[3]*dy[3]);
                            s=p[0]+p[1]+p[2]+p[3];

                            val1=(p[0]*qRed(img_entree->pixel(yi[0],xi[0]))+p[1]*qRed(img_entree->pixel(yi[1],xi[1]))+p[2]*qRed(img_entree->pixel(yi[2],xi[2]))+p[3]*qRed(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val2=(p[0]*qBlue(img_entree->pixel(yi[0],xi[0]))+p[1]*qBlue(img_entree->pixel(yi[1],xi[1]))+p[2]*qBlue(img_entree->pixel(yi[2],xi[2]))+p[3]*qBlue(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val3=(p[0]*qGreen(img_entree->pixel(yi[0],xi[0]))+p[1]*qGreen(img_entree->pixel(yi[1],xi[1]))+p[2]*qGreen(img_entree->pixel(yi[2],xi[2]))+p[3]*qGreen(img_entree->pixel(yi[3],xi[3])))*(1/s);
                            val=qRgb(val1,val3,val2);
                            img_sortie->setPixel(j,i,val);
                        }
                    }

                }
            }
        }
    }


    //les splines Bicubic

    if(methode=="Bicubic")
    {
        double v1,v2,v3;
        for(int i=0;i<ls;i++)
        {
            for(int j=0;j<cs;j++)
            {
                x=i*double(le)/ls;
                y=j*double(ce)/cs;


                xr=x;                             // coordonnées réelles
                yr=y;

                // 1)calcul de l'element le plus proche
                x=floor(x);
                y=floor(y);



                if(x>0 && x<le-1 && y>0 && y<ce-1)
                {
                    v1=Hr(img_entree,x,y-1,xr)*c3(yr-y)+Hr(img_entree,x,y,xr)*c2(yr-y)+Hr(img_entree,x,y+1,xr)*c1(yr-y)+Hr(img_entree,x,y+2,xr)*c0(yr-y);
                    v2=Hg(img_entree,x,y-1,xr)*c3(yr-y)+Hg(img_entree,x,y,xr)*c2(yr-y)+Hg(img_entree,x,y+1,xr)*c1(yr-y)+Hg(img_entree,x,y+2,xr)*c0(yr-y);
                    v3=Hb(img_entree,x,y-1,xr)*c3(yr-y)+Hb(img_entree,x,y,xr)*c2(yr-y)+Hb(img_entree,x,y+1,xr)*c1(yr-y)+Hb(img_entree,x,y+2,xr)*c0(yr-y);

                    val=qRgb(v1,v2,v3);
                    img_sortie->setPixel(j,i,val);
                }
                else{
                    img_sortie->setPixel(j,i,0);
                }
            }
        }
    }

    return img_sortie;

}
