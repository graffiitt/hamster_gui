#ifndef SERIALTRANSLATOR_H
#define SERIALTRANSLATOR_H

#include <QObject>
#include <QSerialPort>

#include <QSerialPortInfo>
#include <QDebug>
#include "../stateWidget/safety.h"

class SerialTranslator : public QObject
{
    Q_OBJECT
public:
    SerialTranslator();
    ~SerialTranslator();

    static SerialTranslator *getInstance();
    void connect(const QSerialPortInfo &port);
    void disconnect();
    bool isConnected();

signals:
    void read(QString data);
    void readMove(QString data);
    void readIO(QString data);
    void write(QString data);
    void connectSignal(bool state);

private slots:
    void readPort();
    void errorPort(QSerialPort::SerialPortError err);
    void writeMCU(QString data);

private:
    static SerialTranslator *_instance;
    Safety *safety;
    QSerialPort *port;
};

#endif // SERIALTRANSLATOR_H
 