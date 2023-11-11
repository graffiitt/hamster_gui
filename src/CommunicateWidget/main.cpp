#include "communicatorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommunicatorWidget w;
    w.show();
    return a.exec();
}
