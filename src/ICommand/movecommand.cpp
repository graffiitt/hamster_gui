#include "movecommand.h"

MoveCommand::MoveCommand()
{
    _data.insert("moveType", MoveType::m_joint);
    _data.insert("pointType", TypePoint::point);
     _data.insert("numberRegister", 0);
    _data.insert("speed", 50);
    _data.insert("acc", 50);

    QJsonObject point; 
    point.insert("coordType", CoordType::joint);
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
    QString typeMove;
    typeMove = _data["moveType"].toInt() ? "line " : "joint";
    return (_data["pointType"].toInt() ? "Pose register " + QString::number(_data["numberRegister"].toInt()) : "Point ") +
          + " " +  typeMove + "    " +
           QString::number(_data["speed"].toInt()) + " speed";
}
