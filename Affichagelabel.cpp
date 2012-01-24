#include "Affichagelabel.h"
#include "Affichage.h"
#include <stdio.h>
#include <QImage>
#include <QRect>
#include "Gris.h"

AffichageLabel::AffichageLabel(Affichage * parent)// , Qt::WindowFlags f):
        //QLabel(parent,f)
{
    picolor_action=false;
    decouper_action=false;
    selectionIsShown = false;
    affichage=parent;
    setMouseTracking(true);
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

}

void AffichageLabel::load(RgbImage im)
{
    rgbimg = im;
}

void AffichageLabel::setaffichage(Affichage *aff)
{
    affichage=aff;
}

void AffichageLabel::imgselect()
{

    int x0=origin.x();
    int y0=origin.y();
    int xF=fin.x();
    int yF=fin.y();
    int w=xF-x0;
    int h=yF-y0;

    QImage *image=new QImage(w, h,QImage::Format_RGB32);
    RgbImage tmp;
    tmp.imgexe =image;

    int i,j=0;
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            tmp[i][j].b=affichage->rgbimg[i+y0][j+x0].b;
            tmp[i][j].g=affichage->rgbimg[i+y0][j+x0].g;
            tmp[i][j].r=affichage->rgbimg[i+y0][j+x0].r;
        }
    }
    affichage->rgbimg.imgexe=tmp.imgexe;
    affichage->image=tmp.imgexe;
    //affichage->setimag(tmp.imgexe);
    affichage->setRgbimg(&tmp);
    affichage->printImag();

}

void AffichageLabel::pixelColor()
{
    picolor_action = true;
    decouper_action=false;
    if(picolor_action==true)
        dialog.open();
}

void AffichageLabel:: selection()
{
    picolor_action = false;
    decouper_action=true;
}



 void AffichageLabel::mouseMoveEvent(QMouseEvent *event)
 {

    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());

 }

void AffichageLabel::mousePressEvent(QMouseEvent *event)
{
    double x = event->pos().x();
    double y = event->pos().y();

    if(event->button() == Qt::LeftButton)
    {
            if(picolor_action && !decouper_action)
            {
                //QRgb pixel =rgbimg.imgexe->pixel((int)x,(int)y);
                QRgb pixel =affichage->rgbimg.imgexe->pixel((int)x,(int)y);
                QColor color = QColor::fromRgb(pixel);
                if(color.isValid())
                {
                    setCursor(Qt::CrossCursor);
                    dialog.setCurrentColor(color);
                }

            }

            if(!picolor_action && decouper_action)
            {
                origin = event->pos();
                rubberBand->setGeometry(QRect(origin, QSize()));
                rubberBand->show();
            }
    }
}
void AffichageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(!picolor_action && decouper_action)
    {
        fin =event->pos();
        rubberBand->hide();
        imgselect();
        decouper_action=false;
        picolor_action=false;
    }

}
