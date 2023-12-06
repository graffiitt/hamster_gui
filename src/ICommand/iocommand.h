#ifndef IOCOMMAND_H
#define IOCOMMAND_H

#include "icommand.h"

class IoCommand : public ICommand
{
public:
    IoCommand();
    ~IoCommand() override;
    virtual QString getDescription() override;

private:
    QString getPin(const int numPin);
    QString getState();
};

#endif
