#ifndef IOWIDGET_H
#define IOWIDGET_H

#include <QWidget>
#include "ioItem.h"

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

private:
    Ui::IOWidget *ui;
    QList<IOItem*> ioItems;
};
#endif
