#include "ioWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IOWidget w;
    w.show();
    return a.exec();
}
