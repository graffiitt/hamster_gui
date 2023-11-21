#include "ioItem.h"

IOItem::IOItem(int number, QWidget *parent) : QWidget(parent)
{
    this->numberPin = number;

    layout = new QHBoxLayout;
    label = new QLabel;
    label->setText("IN[" + QString::number(number) + "]");
    layout->addWidget(label);

    button = new QPushButton;
    button->setText("OFF");
    button->setStyleSheet(falseState);
    layout->addWidget(button);

    this->setLayout(layout);
}

IOItem::~IOItem()
{
    delete label;
    delete button;
    delete layout;
}

void IOItem::setModeIO(bool input)
{
    if (input)
    {
        button->setCheckable(true);
        connect(button, &QPushButton::clicked, this, &IOItem::on_button_cliked);
        label->setText("IN[" + QString::number(numberPin) + "]: ");
    }
    else
    {
        label->setText("OUT[" + QString::number(numberPin) + "]: ");
    }
}

void IOItem::setStateIO(bool state)
{
    if (state)
    {
        button->setText("ON");
        button->setStyleSheet(trueState);
    }
    else
    {
        button->setText("OFF");
        button->setStyleSheet(falseState);
    }
}

int IOItem::getNumberIO()
{
    return this->numberPin;
}

void IOItem::on_button_cliked(bool state)
{
    this->setStateIO(state);
    emit this->changeState(state);
}
