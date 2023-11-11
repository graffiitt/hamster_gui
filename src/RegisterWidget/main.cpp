#include "registerwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegisterWidget w;
    w.show();
    return a.exec();
}
