#include "waitcommand.h"

WaitCommand::WaitCommand()
{
    _data.insert("waitType", WaitType::timer);
    _data.insert("time", 0);
    _data.insert("pinIn", 0);
    _id = Command::Wait;
    _type = "wait";
}


WaitCommand::~WaitCommand()
{

}


QString WaitCommand::getDescription()
{
    QString str;
    switch (_data["waitType"].toInt()) {
    case WaitType::timer:
    {
        str = "wait " + QString::number(_data["time"].toInt()) + " c";
        break;
    }
    case WaitType::ioHigh:
    {
        str = "wait " + QString::number(_data["pinIn"].toInt()) + " In HIGH";
        break;
    }
    case WaitType::ioLow:
    {
        str = "wait " + QString::number(_data["pinIn"].toInt()) + " In LOW";
        break;
    }
    }

    return str;
}
