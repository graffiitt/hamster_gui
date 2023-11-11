#include "execturtorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExecturtorWidget w;
    w.show();
    return a.exec();
}
