#ifndef COMMENTCOMMAND_H
#define COMMENTCOMMAND_H

#include "icommand.h"

class CommentCommand : public ICommand
{
public:
    CommentCommand();
    ~CommentCommand() override;
    virtual QString getDescription() override;
};

#endif // COMMENTCOMMAND_H
