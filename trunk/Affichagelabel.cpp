#include "Affichagelabel.h"
#include <stdio.h>

AffichageLabel::AffichageLabel(QWidget * parent , Qt::WindowFlags f):
        QLabel(parent,f)
{
    picolor_action=false;
    decouper_action=false;
    setMouseTracking(true);

}

void AffichageLabel::load(RgbImage im)
{
    rgbimg=im;
}

void AffichageLabel::pixelcolor()
{
    picolor_action = true;
    decouper_action=false;
    if(picolor_action==true)
        dialog.open();
    //new Colorpicker(this);
}

void AffichageLabel:: selection()
{
    picolor_action = false;
    decouper_action=true;
}


    //void    paintEvent(QPaintEvent *event);
 void AffichageLabel::mouseMoveEvent(QMouseEvent *event)
 {



 }

void AffichageLabel::mousePressEvent(QMouseEvent *event)
{

    double x = event->pos().x();
    double y = event->pos().y();

    if(event->button() == Qt::LeftButton)
    {


            if(picolor_action && !decouper_action)
            {
                QRgb pixel =rgbimg.imgexe->pixel((int)x,(int)y);
                QColor color = QColor::fromRgb(pixel);
                if(color.isValid())
                {
                    setCursor(Qt::CrossCursor);
                    dialog.setCurrentColor(color);
                }
            }
            /*
            if(!picolor_action && decouper_action)
            {

                    if (rect.contains(event->pos())) {
                        rubberBandIsShown = true;
                        rectselection.setTopLeft(event->pos());
                        rectselection.setBottomRight(event->pos());
                        updateRubberBandRegion();
                        setCursor(Qt::CrossCursor);
                    }

            }
            */


    }


}
void AffichageLabel::mouseReleaseEvent(QMouseEvent *event)
{

}

