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
    emit this->connectSignal(false);
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
        safety->setError("mcu not connected");
    }
}

void SerialTranslator::readPort()
{
    QByteArray data = port->readAll();
    qDebug()<<QString(data);


    emit this->read(data);
}

void SerialTranslator::errorPort(QSerialPort::SerialPortError err)
{
    qDebug() << "serial err: " << err;
    switch (err)
    {
    case QSerialPort::NoError:
    {
        safety->setMCU(false);
    }
    case QSerialPort::PermissionError:
    case QSerialPort::ParityError:
    case QSerialPort::BreakConditionError:
    case QSerialPort::FramingError:
    case QSerialPort::WriteError:
    case QSerialPort::ReadError:
    case QSerialPort::UnsupportedOperationError:
    case QSerialPort::UnknownError:
    case QSerialPort::TimeoutError:
    {
        safety->setInfo("port warp error");
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
        this->disconnect();
        break;
    }
    }
    if(err != QSerialPort::NoError)
        safety->setMCU(true);
}

void SerialTranslator::connect(const QSerialPortInfo &port)
{
    this->port->setPort(port);
    this->port->open(QIODevice::ReadWrite);
    if(this->port->isOpen())
    emit this->connectSignal(true);
}
