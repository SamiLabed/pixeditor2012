#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QtGui/QWidget>
#include <QtGui/QPen>
#include <QColorDialog>

#include<QMouseEvent>
#include<QColor>
#include "Affichage.h"


class Colorpicker : public QWidget
{
    Q_OBJECT;
    public:
        Colorpicker(Affichage *aff);

    private:
        Affichage *plateauAffichage;
        //QColor  colorSelected;
        //QImage  image;
        //QPoint  positionCursseur;
        QColor colorDialog;
        QColorDialog dialog;

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
