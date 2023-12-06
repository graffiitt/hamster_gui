#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

enum Command {
    Point,
    Empty,
    Comment,
    Math,
    Wait,
    Jump,
    If,
    Call,
    Io
};

class ICommand
{
protected:
    QJsonObject _data;
    QString _type;
    Command _id;

public:
    virtual ~ICommand();
    virtual QString getDescription();

    QJsonObject getJSONobject();

    void setData(const QJsonObject obj);
    void addObject(QString key, const QJsonValue value);
    QString getType();
    QJsonObject getData();
    Command getId();

};

typedef QList<ICommand *> Programm;

#include "emptycommand.h"
#include "callcommand.h"
#include "commentcommand.h"
#include "ifcommand.h"
#include "jumpcommand.h"
#include "mathcommand.h"
#include "movecommand.h"
#include "waitcommand.h"
#include "iocommand.h"

#endif // ICOMMAND_H
