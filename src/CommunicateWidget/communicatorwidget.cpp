#include "communicatorwidget.h"
#include "ui_communicatorwidget.h"


CommunicatorWidget::CommunicatorWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommunicatorWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("connection");

    mcu = SerialTranslator::getInstance();
}


CommunicatorWidget::~CommunicatorWidget()
{
    delete ui;
    delete mcu;
}

void CommunicatorWidget::updateComPorts()
{
    list = QSerialPortInfo::availablePorts();

    ui->serialBox->clear();
    for (int i = 0; list.size() > i; i++) {
        ui->serialBox->addItem(list.at(i).portName());
    }
}


void CommunicatorWidget::on_closeButton_clicked()
{
    this->close();
}


void CommunicatorWidget::on_connectButton_clicked()
{
    mcu->connect(list.at(ui->serialBox->currentIndex()));
    if(mcu->isConnected())
    {
        ui->connectButton->setDisabled(true);
        ui->msgLabel->setText("connected");
        ui->commandLine->setEnabled(true);
        ui->sendButton->setEnabled(true);
    }
}


void CommunicatorWidget::on_disconnectButton_clicked()
{
    mcu->disconnect();
    if(!mcu->isConnected())
    {
        ui->connectButton->setDisabled(false);
        ui->msgLabel->setText("disconnected");
        ui->commandLine->setEnabled(false);
        ui->sendButton->setEnabled(false);
    }
}


void CommunicatorWidget::on_sendButton_clicked()
{
    QString cmd = ui->commandLine->text();
    ui->commandList->insertItem(0, cmd);
    if(ui->commandList->count() >= 30)
    {
        delete ui->commandList->takeItem(ui->commandList->count()-1);
    }

    mcu->write(cmd);
}


void CommunicatorWidget::show()
{
    this->updateComPorts();
    ui->msgLabel->setText(mcu->isConnected()? "connected" : "disconnected");
    this->QWidget::show();
}


void CommunicatorWidget::on_commandList_itemActivated(QListWidgetItem *item)
{
    ui->commandLine->setText(item->text());
}

