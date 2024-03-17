#ifndef IOWIDGET_H
#define IOWIDGET_H

#include <QWidget>
#include "QEventLoop"
#include "ioItem.h"
#include "../stateWidget/safety.h"
#include "../CommunicateWidget/serialtranslator.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class IOWidget;
}
QT_END_NAMESPACE

class IOWidget : public QWidget
{
    Q_OBJECT

public:
    IOWidget(QWidget *parent = nullptr);
    ~IOWidget();
    static void changePin(int numPin, bool state);

private slots:
    
    void requestMCU(bool state);
  //  void readMCUpackage(QString data);

private:
    Ui::IOWidget *ui;

    static QList<IOItem *> ioItems;
    static Safety *safety;
    static SerialTranslator *serial;
};
#endif
