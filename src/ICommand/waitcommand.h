#ifndef WAITCOMMAND_H
#define WAITCOMMAND_H

#include "icommand.h"

enum WaitType{
    timer,
    ioHigh,
    ioLow
};


class WaitCommand : public ICommand
{
public:
    WaitCommand();
    ~WaitCommand() override;
    virtual QString getDescription() override;

};

#endif // WAITCOMMAND_H
