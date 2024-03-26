#ifndef COMMUNICATORWIDGET_H
#define COMMUNICATORWIDGET_H

#include <QDialog>
#include <QTranslator>
#include <QListWidgetItem>
#include "serialtranslator.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class CommunicatorWidget;
}
QT_END_NAMESPACE

class CommunicatorWidget : public QDialog
{
    Q_OBJECT

public:
    CommunicatorWidget(QWidget *parent = nullptr);
    ~CommunicatorWidget();

    void updateComPorts();
    void show();

private slots:
    void on_closeButton_clicked();
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_sendButton_clicked();
    void on_commandList_itemActivated(QListWidgetItem *item);
    void connectSlot(bool state);

private:
    QList<QSerialPortInfo> list;
    Ui::CommunicatorWidget *ui;
    SerialTranslator *mcu;
    QTranslator translate;

    void updateLanguage();
};
#endif // COMMUNICATORWIDGET_H
