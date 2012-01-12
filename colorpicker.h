#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QtGui/QWidget>
#include <QtGui/QPen>
#include <QColorDialog>
#include <Affichage.h>
#include<QMouseEvent>
#include<QColor>

class ColorPicker : public QWidget
{
    public:
        ColorPicker();
        ColorPicker(Affichage *plateauAffichage);

    private:
        Affichage *plateauAffichage;
        QColor  colorSelected;
        QImage  image;
        QPoint  positionCursseur;
        QColor colorDialog;

    protected:
        void    mouseMoveEvent(QMouseEvent *event);
        void    mousePressEvent(QMouseEvent *event);
        void    mouseReleaseEvent(QMouseEvent *event);


    signals:
        //void    colorSelected(const QColor &couleur);


    public slots:
        //void    setDialogColeur(const QColor &couleur);




};

#endif // COLORPICKER_H
