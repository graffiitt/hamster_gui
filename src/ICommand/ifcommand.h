#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "icommand.h"
#include "mathcommand.h"

enum MathBehivor
{
    equal,
    less,
    more
};

class IfCommand : public ICommand
{
public:
    IfCommand();
    ~IfCommand() override;
    virtual QString getDescription() override;

private:
    QString getLine();
    QString getItem(int number);
};

#endif // IFCOMMAND_H
