#include "jumpcommand.h"

JumpCommand::JumpCommand()
{
    _data.insert("lbl", 1);
    _data.insert("mode", JumpMode::lbl);
    _id = Command::Jump;
    _type = "jump";
}


JumpCommand::~JumpCommand()
{

}


QString JumpCommand::getDescription()
{
    return (_data["mode"].toInt() ? "jump_lbl " : "lbl ") +
                 QString::number(_data["lbl"].toInt());

}
