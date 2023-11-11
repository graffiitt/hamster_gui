#ifndef REGISTERDTO_H
#define REGISTERDTO_H

#include <QObject>
#include <QList>
#include <QDebug>

#include "registerbase.h"
#include "../JSONmodule/jsonmodule.h"


class RegisterDTO: public QObject
{
    Q_OBJECT
public:
    RegisterDTO();
    ~RegisterDTO();

    void deleteObjects();
    static int getSize();
    static void changeRegister(int num, QJsonValue data, QString key);
    static void mergeObject(int num, QJsonObject obj);
    static QJsonValue getRegister(int num);
    static QJsonValue getRawRegister(int num);

    QString getLine(QString type, int line);

   private:
    static Registers *_registers;
    QString _path;
    JSONmodule *json;

    void initObjectPool();

signals:
    void save();

private slots:
    void saveToJson();

};

#endif // REGISTERDTO_H
