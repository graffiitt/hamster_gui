#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <QDebug>

#include "../stateWidget/safety.h"


class JSONloader
{
public:
    JSONloader();

    void save(QString path, QString item, QJsonValue obj);
    QJsonObject read(QString path);


protected:
    void changeName(QString name);


private:
    Safety *safety;
};

#endif // JSONLOADER_H
