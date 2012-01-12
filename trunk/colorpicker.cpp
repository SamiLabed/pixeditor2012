#include "colorpicker.h"

ColorPicker::ColorPicker(Affichage *plateau)
{
    plateauAffichage=plateau;


}

void ColorPicker::mouseMoveEvent(QMouseEvent *event)
{

}
void ColorPicker::mousePressEvent(QMouseEvent *event)
{
    double x = event->pos().x();
    double y = event->pos().y();

    //double height_principale= plateauAffichage->height();
    //double wight_principale= plateauAffichage->width();

    QRgb pixel =plateauAffichage->image->pixel((int)x,(int)y);
    QColor color = QColor::fromRgb(pixel);
    if(color.isValid())
        colorDialog = QColorDialog::getColor(color,this);
        //colorDialog.setCurrentColor(color);

}
void ColorPicker::mouseReleaseEvent(QMouseEvent *event)
{

}
