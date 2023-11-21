#include "serialtranslator.h"

SerialTranslator *SerialTranslator::_instance = 0;

SerialTranslator::SerialTranslator()
{
    safety = Safety::getInstance();
    port = new QSerialPort();

    QObject::connect(port, &QSerialPort::readyRead, this, &SerialTranslator::readPort, Qt::DirectConnection);
    QObject::connect(port, &QSerialPort::errorOccurred, this, &SerialTranslator::errorPort, Qt::DirectConnection);
    QObject::connect(this, &SerialTranslator::write, this, &SerialTranslator::writeMCU);
}

SerialTranslator::~SerialTranslator()
{
    delete port;
}

SerialTranslator *SerialTranslator::getInstance()
{
    if (!_instance)
        _instance = new SerialTranslator();
    return _instance;
}

void SerialTranslator::disconnect()
{
    this->port->close();
}

bool SerialTranslator::isConnected()
{
    return port->isOpen();
}

void SerialTranslator::writeMCU(QString data)
{
    if (port->isOpen())
    {
        port->write(data.toLatin1());
    }
    else
    {
        safety->setInfo("mcu not connected");
    }
}

void SerialTranslator::readPort()
{
    emit this->read(port->readAll());
}

void SerialTranslator::errorPort(QSerialPort::SerialPortError err)
{
    qDebug() << "serial err: " << err;
    switch (err)
    {
    case QSerialPort::NoError:
    {
        safety->setInfo("");
        break;
    }
    case QSerialPort::OpenError:
    {
        safety->setInfo("port open error");
        break;
    }
    case QSerialPort::DeviceNotFoundError:
    {
        safety->setInfo("port not found");
        break;
    }
    case QSerialPort::NotOpenError:
    {
        safety->setInfo("port already close");
        break;
    }
    case QSerialPort::ResourceError:
    {
        safety->setError("port connection lose");
        break;
    }
    }
}

void SerialTranslator::connect(const QSerialPortInfo &port)
{
    this->port->setPort(port);
    this->port->open(QIODevice::ReadWrite);
    emit this->connect();
}
