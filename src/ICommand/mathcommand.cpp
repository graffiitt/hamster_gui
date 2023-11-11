#include "mathcommand.h"

MathCommand::MathCommand()
{
    _data.insert("regOutType", TypeItem::reg);
    _data.insert("regOut", 0);
    _data.insert("poseReg", 0);
    _data.insert("poseRegItem", 1);

    _data.insert("operator", MathOperator::none);
    _data.insert("itemType_1", TypeItem::number);
    _data.insert("itemType_2", TypeItem::number);

    _data.insert("number_1", 0);
    _data.insert("register_1", 0);
    _data.insert("poseReg_1", 0);
    _data.insert("poseRegItem_1", 1);

    _data.insert("number_2", 0);
    _data.insert("register_2", 0);
    _data.insert("poseReg_2", 0);
    _data.insert("poseRegItem_2", 1);

    _id = Command::Math;
    _type = "math";
}


MathCommand::~MathCommand()
{

}


QString MathCommand::getDescription()
{
    QString str;

    switch (_data.value("operator").toInt()) {
    case MathOperator::none:
    {
        str = this->getItem(0) + " = " + this->getItem(1);
        break;
    }
    case MathOperator::summ:
    {
        str = this->getItem(0) + " = " + this->getItem(1) + " + " + this->getItem(2);
        break;
    }
    case MathOperator::minus:
    {
        str = this->getItem(0) + " = " + this->getItem(1) + " - " + this->getItem(2);
        break;
    }
    case MathOperator::divide:
    {
        str = this->getItem(0) + " = " + this->getItem(1) + " / " + this->getItem(2);
        break;
    }
    case MathOperator::multiplication:
    {
        str = this->getItem(0) + " = " + this->getItem(1) + " * " + this->getItem(2);
        break;
    }
    }

    return str;
}


QString MathCommand::getItem(int it)
{
    QString str;
    switch (it) {
    case 0:
    {
        switch (_data.value("regOutType").toInt()) {
        case TypeItem::posReg:
        {
            str = "PR[" + QString::number(_data.value("poseReg").toInt()) +
                    ", " + QString::number(_data.value("poseRegItem").toInt()) + "]" ;
            break;
        }
        case TypeItem::reg:
        {
            str = "R[" + QString::number(_data.value("regOut").toInt()) + "]";
            break;
        }
        }
        break;
    }
    case 1:
    {
        switch (_data.value("itemType_1").toInt()) {
        case TypeItem::number:
        {
            str = QString::number(_data.value("number_1").toInt());
            break;
        }
        case TypeItem::posReg:
        {
            str = "PR[" + QString::number(_data.value("poseReg_1").toInt()) +
                    ", " + QString::number(_data.value("poseRegItem_1").toInt()) + "]" ;
            break;
        }
        case TypeItem::reg:
        {
            str = "R[" + QString::number(_data.value("register_1").toInt()) + "]";
            break;
        }
        }
        break;
    }
    case 2:
    {
        switch (_data.value("itemType_2").toInt()) {
        case TypeItem::number:
        {
            str = QString::number(_data.value("number_2").toInt());
            break;
        }
        case TypeItem::posReg:
        {
            str = "PR[" + QString::number(_data.value("poseReg_2").toInt()) +
                    ", " + QString::number(_data.value("poseRegItem_2").toInt()) + "]" ;
            break;
        }
        case TypeItem::reg:
        {
            str = "R[" + QString::number(_data.value("register_2").toInt()) + "]";
            break;
        }
        }
        break;
    }
    }

    return str;
}
