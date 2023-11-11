#ifndef EMPTYCOMMAND_H
#define EMPTYCOMMAND_H

#include "icommand.h"

class EmptyCommand: public ICommand
{
public:
    EmptyCommand();
    ~EmptyCommand() override;
    virtual QString getDescription() override;

};

#endif // EMPTYCOMMAND_H
