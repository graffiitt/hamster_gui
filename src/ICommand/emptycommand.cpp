#include "emptycommand.h"

EmptyCommand::EmptyCommand()
{
    _id = Command::Empty;
    _type = "empty";
}

EmptyCommand::~EmptyCommand()
{

}

QString EmptyCommand::getDescription()
{
    return "";
}

