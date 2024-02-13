#include "icommand.h"

ICommand::~ICommand()
{
}


QString ICommand::getDescription()
{
    return "icommand";
}


QJsonObject ICommand::getJSONobject()
{
    QJsonObject emptyObj;
    emptyObj["id"] = _id;
    emptyObj["type"] = _type;
    emptyObj["description"] = _data;
    return emptyObj;
}

void ICommand::setData(const QJsonObject obj)
{
    _data = obj;
}

void ICommand::addObject(QString key, const QJsonValue value)
{
    _data.insert(key, value);
}

QString ICommand::getType()
{
    return _type;
}

QJsonObject ICommand::getData()
{
    return _data;
}

Command ICommand::getId()
{
    return _id;
}
