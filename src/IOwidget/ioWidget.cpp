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
    qDebug() << "iowidget " << data;
}

void IOWidget::changePin(int numPin, bool state)
{
    QString str;
    QEventLoop loop;

 qDebug() << "event loop";

    connect(safety, &Safety::outError, [&]()
            {
            // segmentation fault
            qDebug()<<"safety err io";
            if (serial->isConnected())
            loop.exit(0); });

    connect(serial, &SerialTranslator::read, [&]()
            { 
            ioItems[numPin]->setStateIO(state);
            loop.exit(0); });

    str = "IO010050" + QString::number(numPin) + QString::number(state);
    serial->write(str);

    if (serial->isConnected())
        loop.exec();
    else
        safety->setError("mcu not connected");
    qDebug() << "mmf";
    disconnect(safety, &Safety::outError, 0, 0);
    disconnect(serial, &SerialTranslator::read, 0, 0);
}

void IOWidget::requestMCU(bool state)
{
    IOItem *item = qobject_cast<IOItem *>(sender());
    this->changePin(item->getNumberIO(), state);
}
