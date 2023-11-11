#include "registerdto.h"

Registers *RegisterDTO::_registers = new Registers();

RegisterDTO::RegisterDTO()
{
    _path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
            "/GraffitRobotics/register.json";
           // qDebug()<<"reg path  "<<_path;
    json = new JSONmodule();

    this->initObjectPool();

    QObject::connect(this, &RegisterDTO::save, this, &RegisterDTO::saveToJson, Qt::DirectConnection);
}

RegisterDTO::~RegisterDTO()
{
    delete json;
}

void RegisterDTO::deleteObjects()
{
    for (int i = _registers->size(); i > 0; i--)
        delete _registers->takeAt(i - 1);
    delete _registers;
}

QString RegisterDTO::getLine(QString type, int line)
{
    if (type == "reg")
        return _registers->value(line)->getLineRegister();
    else
        return _registers->value(line)->getLinePoseRegister();
}

void RegisterDTO::saveToJson()
{
    json->saveFile(_registers, _path);
}

void RegisterDTO::initObjectPool()
{
    if (_registers->size() == 0)
    {
        _registers->append(json->openFile(_path, ""));
        if (_registers->size() == 0)
            for (int i = 0; i < 50; i++)
                _registers->append(new RegisterBase());
    }
}

int RegisterDTO::getSize()
{
    return _registers->size();
}

void RegisterDTO::changeRegister(int num, QJsonValue data, QString key)
{
    if (num <= 49 && num >= 0)
    {
        _registers->value(num)->set(key, data);
    }
}

void RegisterDTO::mergeObject(int num, QJsonObject obj)
{
    if (num <= 49 && num >= 0)
    {
        _registers->value(num)->mergeData(obj);
    }
}

QJsonValue RegisterDTO::getRegister(int num)
{
    if (num <= 49 && num >= 0)
    {
        return _registers->value(num)->get("regData");
    }
    else
        return QJsonValue();
}

QJsonValue RegisterDTO::getRawRegister(int num)
{
    if (num <= 49 && 0 <= num)
    {
        return _registers->value(num)->getData();
    }
    else
        return QJsonValue();
}
