#include "movecommand.h"

MoveCommand::MoveCommand()
{
    _data.insert("moveType", "linear");
    _data.insert("pointType", TypePoint::point);
    _data.insert("speed", 50);
    _data.insert("acc", 50);

    QJsonObject point; 
    point.insert("coordType", "joint");
    point.insert("j1", 0);
    point.insert("j2", 0);
    point.insert("j3", 0);
    point.insert("j4", 0);
    _data.insert("point", point);

    _id = Point;
    _type = "point";
}

MoveCommand::~MoveCommand()
{
}

QString MoveCommand::getDescription()
{
    return (_data["pointType"].toInt() ? "Pose register " : "Point ") +
           _data["moveType"].toString() + "    " +
           QString::number(_data["speed"].toInt()) + " speed";
}
