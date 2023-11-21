#ifndef IOITEM_H
#define IOITEM_H

#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class IOItem : public QWidget
{
    Q_OBJECT
public:
    IOItem(int number = 0, QWidget *parent = nullptr);
    ~IOItem();

    void setModeIO(bool input);
    void setStateIO(bool state);
    int getNumberIO();

signals:
    void changeState(bool state);

private slots:
    void on_button_cliked(bool state);

private:
    int numberPin;
    QLabel *label;
    QHBoxLayout *layout;
    QPushButton *button;

    QString falseState = "background-color: #ff0000; color:#000000";
    QString trueState = "background-color: #00ff00; color:#000000";
};

#endif