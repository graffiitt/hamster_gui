#include "ioWidget.h"
#include "ui_ioWidget.h"

QList<IOItem *> IOWidget::ioItems;
Safety *IOWidget::safety;
SerialTranslator *IOWidget::serial;

IOWidget::IOWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::IOWidget)
{
    ui->setupUi(this);

    QVBoxLayout *vboxIN = new QVBoxLayout;
    for (size_t i = 0; i < 8; i++)
    {
        IOItem *item = new IOItem(i, true);
        ioItems.append(item);
        vboxIN->addWidget(item);
        connect(item, &IOItem::changeState, this, &IOWidget::requestMCU);
    }
    ui->inputBox->setLayout(vboxIN);

    QVBoxLayout *vboxOUT = new QVBoxLayout;
    for (size_t i = 0; i < 8; i++)
    {
        IOItem *item = new IOItem(i, false);
        ioItems.append(item);
        vboxOUT->addWidget(item);
    }
    ui->outputBox->setLayout(vboxOUT);

    safety = Safety::getInstance();
    serial = SerialTranslator::getInstance();
}

IOWidget::~IOWidget()
{
    delete ui;
    for (QList<IOItem *>::iterator it = ioItems.begin(); it < ioItems.end(); it++)
        delete *it;
    ioItems.clear();
}

void IOWidget::changePin(int numPin, bool state)
{
    QEventLoop loop;
    QString str = "IO010050" + QString::number(numPin) + QString::number(state);
   
    if (!serial->isConnected())
    {
        safety->setError("mcu not connect");
        return;
    }

    connect(serial, &SerialTranslator::readIO, [&](QString msg)
            {
            ioItems[msg[6].digitValue()]->setStateIO(msg[8].digitValue());
            loop.exit(); });

    serial->write(str);
    loop.exec();

    disconnect(serial, &SerialTranslator::read, 0, 0);
}

// cmd = 0 -- wait state false
// cmd = 1 -- wait state true
// cmd = 3 -- read pin
// 0 -- false  2 -- true
int IOWidget::readPin(int numPin, int cmd)
{
    int state = 0; // false

    switch (cmd)
    {
    case 0:
        /* code */
        break;
    case 1:
        break;
    case 2:
        break;
    }

    qDebug() << numPin;
    return state;
}

// изменение через ui
void IOWidget::requestMCU(bool state)
{
    IOItem *item = qobject_cast<IOItem *>(sender());
    this->changePin(item->getNumberIO(), state);
}
