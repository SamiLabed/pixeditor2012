#include "colorpicker.h"
#include <stdio.h>

Colorpicker::Colorpicker(Affichage *aff)
{
    plateauAffichage=aff;
    dialog.open();// = QColorDialog(QWidget *parent=0);
    show();

}

void Colorpicker::mouseMoveEvent(QMouseEvent *event)
{
    //double x = event->pos().x();
    //double y = event->pos().y();

    //double height_principale= plateauAffichage->height();
    //double wight_principale= plateauAffichage->width();

    //QRgb pixel =plateauAffichage->image->pixel((int)x,(int)y);
    //QColor color = QColor::fromRgb(pixel);
    //if(color.isValid())
        //colorDialog = QColorDialog::getColor(color,this);
    //    dialog.setCurrentColor(color);

}
void Colorpicker::mousePressEvent(QMouseEvent *event)
{

    //double x = event->pos().x();
    //double y = event->pos().y();

    //double height_principale= plateauAffichage->height();
    //double wight_principale= plateauAffichage->width();

    //QRgb pixel =plateauAffichage->image->pixel((int)x,(int)y);
    //QColor color = QColor::fromRgb(pixel);
    //if(color.isValid())
    //    //colorDialog = QColorDialog::getColor(color,this);
    //    dialog.setCurrentColor(color);

}
void Colorpicker::mouseReleaseEvent(QMouseEvent *event)
{

}
