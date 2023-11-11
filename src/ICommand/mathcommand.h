#ifndef MATHCOMMAND_H
#define MATHCOMMAND_H

#include "icommand.h"


enum MathOperator{
    none,
    summ,
    minus,
    divide,
    multiplication

};
enum TypeItem{
    number,
    reg,
    posReg
};

class MathCommand : public ICommand
{
public:
    MathCommand();
    ~MathCommand() override;

    QString getDescription() override;

private:
    QString getItem(int it);

};

#endif // MATHCOMMAND_H
