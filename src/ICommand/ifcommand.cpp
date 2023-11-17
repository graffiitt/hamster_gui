#include "ifcommand.h"

IfCommand::IfCommand()
{
    _data.insert("operator", MathBehivor::equal);

    _data.insert("itemType_1", TypeItem::number);
    _data.insert("itemType_2", TypeItem::number);

    _data.insert("number_1", 0);
    _data.insert("register_1", 0);
    _data.insert("poseReg_1", 0);
    _data.insert("poseRegItem_1", 1);
    _data.insert("ioPin_1", 1);
    _data.insert("ioPinState_1", 0);

    _data.insert("number_2", 0);
    _data.insert("register_2", 0);
    _data.insert("poseReg_2", 0);
    _data.insert("poseRegItem_2", 1);
    _data.insert("ioPin_2", 1);
    _data.insert("ioPinState_2", 0);

    _data.insert("jumpLBL", 0);

    _id = Command::If;
    _type = "if";
}

IfCommand::~IfCommand()
{
}

QString IfCommand::getDescription()
{
    return this->getLine();
}

QString IfCommand::getLine()
{
    QString str;
    switch (_data["operator"].toInt())
    {
    case MathBehivor::equal:
    {
        str = this->getItem(1) + " = " + this->getItem(2);
        break;
    }
    case MathBehivor::less:
    {
        str = this->getItem(1) + " < " + this->getItem(2);
        break;
    }
    case MathBehivor::more:
    {
        str = this->getItem(1) + " > " + this->getItem(2);
        break;
    }
    }
    if (_data.value("itemType_1").toInt() == TypeItem::IO)
        str = this->getItem(1);

    return "if " + str + " jumpLBL " + QString::number(_data.value("jumpLBL").toInt());
}

QString IfCommand::getItem(int number)
{
    QString str;

    switch (_data.value(QString("itemType_%1").arg(number)).toInt())
    {
    case TypeItem::number:
    {
        str = QString::number(_data.value(QString("number_%1").arg(number)).toInt());
        break;
    }
    case TypeItem::posReg:
    {
        str = "PR[" + QString::number(_data.value(QString("poseReg_%1").arg(number)).toInt()) +
              ", " + QString::number(_data.value(QString("poseRegItem_%1").arg(number)).toInt()) + "]";
        break;
    }
    case TypeItem::reg:
    {
        str = "R[" + QString::number(_data.value(QString("register_%1").arg(number)).toInt()) + "]";
        break;
    }
    case TypeItem::IO:
    {
        str = "IO[" + QString::number(_data["ioPin_1"].toInt()) + "]" +
             " = " + (_data.value("ioPinState_1").toInt() ? "TRUE" : "FALSE");
        break;
    }
    }

    return str;
}
