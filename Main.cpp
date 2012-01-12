#include <QtGui/QApplication>
#include "PixEditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PixEditor w;
    w.show();
    return a.exec();
}
