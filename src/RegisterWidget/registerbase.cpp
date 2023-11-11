#include "registerbase.h"

RegisterBase::RegisterBase()
{
    _data.insert("regData", 0);
    _data.insert("regName", "");
    _data.insert("poseRegItem_1", 0);
    _data.insert("poseRegItem_2", 0);
    _data.insert("poseRegItem_3", 0);
    _data.insert("poseRegItem_4", 0);

}


QJsonObject RegisterBase::getData()
{
    return _data;
}


void RegisterBase::setData(QJsonObject data)
{
    this->_data = data;
}

void RegisterBase::mergeData(QJsonObject data)
{
    for (auto it = data.constBegin(); it != data.constEnd(); it++)
        this->_data.insert(it.key(), it.value());
}


QString RegisterBase::getLineRegister()
{
    return QString::number(_data.value("regData").toInt());
}


QString RegisterBase::getLinePoseRegister()
{
    QString str;
    return "'" + _data["regName"].toString() + "'";
}


void RegisterBase::set(QString key, QJsonValue value)
{
    this->_data[key] = value;
}


QJsonValue RegisterBase::get(QString key)
{
    return _data[key];
}


