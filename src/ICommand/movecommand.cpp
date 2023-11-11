#include "movecommand.h"

MoveCommand::MoveCommand()
{
    _data.insert("moveType", "linear");
    _data.insert("speed", 50);
    _data.insert("acc", 50);

    _id = Point;
    _type = "point";

}

MoveCommand::~MoveCommand()
{

}


QString MoveCommand::getDescription()
{
    return  "Point    " +
            _data["moveType"].toString() + "    " +
            QString::number(_data["speed"].toInt()) + " speed";
}

