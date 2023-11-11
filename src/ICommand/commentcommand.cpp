#include "commentcommand.h"



CommentCommand::CommentCommand()
{
    _data.insert("data", "");
        _id = Command::Comment;
        _type = "commentary";
}

CommentCommand::~CommentCommand()
{

}

QString CommentCommand::getDescription()
{
    return "# " + _data["data"].toString();
}
