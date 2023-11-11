#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "icommand.h"
#include "mathcommand.h"

enum MathBehivor {
    equal,
    more,
    less
};

class IfCommand : public ICommand
{
public:
    IfCommand();
    ~IfCommand() override;
    virtual QString getDescription() override;

private:
    QString getLine();
};

#endif // IFCOMMAND_H
