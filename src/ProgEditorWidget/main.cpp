#include "programmeditorwidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProgrammEditorWidget w;    
    w.show();
    return a.exec();
}
