#ifndef CALLCOMMAND_H
#define CALLCOMMAND_H

#include "icommand.h"

class CallCommand: public ICommand
{
public:
    CallCommand();
    ~CallCommand() override;
    virtual QString getDescription() override;
};

#endif // CALLCOMMAND_H
