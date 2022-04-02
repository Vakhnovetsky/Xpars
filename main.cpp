#include <QtGui/QApplication>
#include "xpars.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Xpars w;
    w.show();
    return a.exec();
}
