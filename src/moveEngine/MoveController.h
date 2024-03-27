#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

#include <QTranslator>
#include <QDialog>
#include <QDebug>

#include "../CommunicateWidget/communicatorwidget.h"

// #include "../ProgEditorWidget/programmeditorwidget.h"
// #include "../stateWidget/safety.h"
// #include "../ExectutorWidget/execturtorwidget.h"
// #include "../RegisterWidget/registerwidget.h"
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

    void show();
    bool isActive();

    virtual void closeEvent(QCloseEvent *e) override;

private:
    Ui::MoveController *ui;
    SerialTranslator *mcu;
    
    bool activeWindow;
};
#endif // MAINWINDOW_H
