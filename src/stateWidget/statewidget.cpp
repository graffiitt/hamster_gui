#include "statewidget.h"
#include "ui_statewidget.h"


StateWidget::StateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StateWidget)
{
    ui->setupUi(this);

    stateErr = false;
}


StateWidget::~StateWidget()
{
    delete ui;
}


void StateWidget::setError(bool state)
{
    if (stateErr != state)
    {
        state ? ui->faultLabel->setStyleSheet(redColor) : ui->faultLabel->setStyleSheet("");
        stateErr = state;
    }
}


void StateWidget::setInfo(QString msg)
{
    ui->errorLabel->setText(msg);
}


void StateWidget::setRunIcon(bool state)
{
    state ? ui->runLabel->setStyleSheet(greenColor) : ui->runLabel->setStyleSheet("");
}

void StateWidget::setStepMode(bool state)
{
    state ? ui->stepLabel->setStyleSheet(yellowColor) : ui->stepLabel->setStyleSheet("");
}

void StateWidget::setCurrentLine(int line)
{
    ui->lineNumLabel->setText("line " + QString::number(line + 1));
}

void StateWidget::setOpenProg(QString name)
{
    ui->prgNameLabel->setText(name);
}

void StateWidget::setIOicon(bool state)
{
    state ? ui->ioLabel->setStyleSheet(greenColor) : ui->stepLabel->setStyleSheet("");

}

void StateWidget::setMCUicon(bool state)
{
    state ? ui->mcuLabel->setStyleSheet(yellowColor) : ui->stepLabel->setStyleSheet("");

}

bool StateWidget::getStateError()
{
    return stateErr;
}

