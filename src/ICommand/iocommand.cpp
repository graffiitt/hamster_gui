#include "iocommand.h"

enum PINOUT
{
    output,
    input,
};

IoCommand::IoCommand()
{
    _data.insert("pin", 0);
    _data.insert("state", 0);
    _data.insert("type", PINOUT::output);
    _id = Command::Io;
    _type = "io";
}

IoCommand::~IoCommand()
{
}

QString IoCommand::getDescription()
{
    return getPin(_data["pin"].toInt()) + "";
}

QString IoCommand::getPin(const int numPin)
{
    QString str;
    if (_data["type"].toInt() == PINOUT::input)
        str = "DI";
    else
        str = "DO";

    return str + "[" + QString::number(numPin) + "]" + getState();
}

QString IoCommand::getState()
{
    if (_data["state"].toInt())
    return "TRUE";
    else
    return "FALSE";
}