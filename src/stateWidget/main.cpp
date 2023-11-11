#include "statewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StateWidget w;
    w.show();
    return a.exec();
}
