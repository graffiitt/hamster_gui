#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "icommand.h"

enum MoveType
{
    m_joint,
    m_linear,
};

enum CoordType
{
    joint,
    cartesian
};

enum TypePoint
{
    point,
    poseRegister
};

class MoveCommand : public ICommand
{
public:
    MoveCommand();
    ~MoveCommand() override;
    virtual QString getDescription() override;
};

#endif // MOVECOMMAND_H
