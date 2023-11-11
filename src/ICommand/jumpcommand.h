#ifndef JUMPCOMMAND_H
#define JUMPCOMMAND_H

#include "icommand.h"


enum JumpMode {
    lbl,
    jump
};


class JumpCommand : public ICommand
{
public:
    JumpCommand();
    ~JumpCommand() override;
    virtual QString getDescription() override;
};

#endif // JUMPCOMMAND_H
