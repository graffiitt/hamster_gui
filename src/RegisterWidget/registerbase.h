#ifndef REGISTERBASE_H
#define REGISTERBASE_H

#include <QJsonObject>



class RegisterBase
{
public:
    RegisterBase();
    QJsonObject getData();
    void setData(QJsonObject data);
    void mergeData(QJsonObject data);
    QString getLineRegister();
    QString getLinePoseRegister();

    void set(QString key, QJsonValue value);
    QJsonValue get(QString key);

private:
    QJsonObject _data;

};

typedef QList<RegisterBase *> Registers;

#endif // REGISTERBASE_H
