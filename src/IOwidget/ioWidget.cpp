#include "ioWidget.h"
#include "ui_ioWidget.h"

QList<IOItem *> IOWidget::ioItems;

IOWidget::IOWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::IOWidget)
{
    ui->setupUi(this);

    QVBoxLayout *vboxIN = new QVBoxLayout;
    for (size_t i = 0; i < 8; i++)
    {
        IOItem *item = new IOItem(i);
        item->setModeIO(true);
        ioItems.append(item);
        vboxIN->addWidget(item);
        connect(item, &IOItem::changeState, this, &IOWidget::requestMCU);
    }
    ui->inputBox->setLayout(vboxIN);

    QVBoxLayout *vboxOUT = new QVBoxLayout;
    for (size_t i = 0; i < 8; i++)
    {
        IOItem *item = new IOItem(i);
        item->setModeIO(false);
        ioItems.append(item);
        vboxOUT->addWidget(item);
    }
    ui->outputBox->setLayout(vboxOUT);

    safety = Safety::getInstance();
    serial = SerialTranslator::getInstance();

    connect(serial, &SerialTranslator::read, this, &IOWidget::readMCUpackage, Qt::DirectConnection);
}

IOWidget::~IOWidget()
{
    delete ui;
    for (QList<IOItem *>::iterator it = ioItems.begin(); it < ioItems.end(); it++)
        delete *it;
    ioItems.clear();
}

void IOWidget::readMCUpackage(QString data)
{

}

void IOWidget::changePin(int numPin, bool state)
{
    qDebug() << "io widget   " << numPin << " " << state;

}

void IOWidget::requestMCU(bool state)
{
    IOItem *item = qobject_cast<IOItem *>(sender());
    this->changePin(item->getNumberIO(), state);
}
