#include "callcommand.h"


CallCommand::CallCommand()
{
    _data.insert("namePrg", "");
    _id = Command::Call;
    _type = "call";
}

CallCommand::~CallCommand()
{

}

QString CallCommand::getDescription()
{
    return "call " + _data["namePrg"].toString();
}


