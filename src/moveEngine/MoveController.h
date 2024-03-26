#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTranslator>
#include <QDialog>
#include <QDebug>

// #include "../ProgEditorWidget/programmeditorwidget.h"
// #include "../stateWidget/safety.h"
// #include "../ExectutorWidget/execturtorwidget.h"
// #include "../RegisterWidget/registerwidget.h"
// #include "../CommunicateWidget/communicatorwidget.h"
// #include "../IOwidget/ioWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MoveController;
}
QT_END_NAMESPACE

class MoveController : public QDialog
{
    Q_OBJECT
public:
    MoveController(QWidget *parent = nullptr);
    ~MoveController();

private:
    Ui::MoveController *ui;
};
#endif // MAINWINDOW_H
