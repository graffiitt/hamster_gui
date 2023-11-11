#include "ifcommand.h"

IfCommand::IfCommand()
{
    _data.insert("operator", MathBehivor::equal);
    _id = Command::If;
    _type = "if";
}

IfCommand::~IfCommand()
{

}

QString IfCommand::getDescription()
{
    return "if";
}

QString IfCommand::getLine()
{
//    switch () {

//    }
    return "";
}
