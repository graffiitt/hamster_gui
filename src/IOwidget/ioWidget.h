#ifndef IOWIDGET_H
#define IOWIDGET_H

#include <QWidget>
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

private slots:
    void requestMCU(bool state);
    void readMCUpackage(QString data);

private:
    Ui::IOWidget *ui;
    QList<IOItem *> ioItems;

    Safety *safety;
    SerialTranslator *serial;
};
#endif
