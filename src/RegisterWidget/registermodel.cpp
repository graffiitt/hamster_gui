#include "registermodel.h"

RegisterModel::RegisterModel(QObject *parent) : QAbstractTableModel(parent)
{
    dto = new RegisterDTO();
}


RegisterModel::~RegisterModel()
{
    dto->deleteObjects();
    delete dto;
}


void RegisterModel::resetModel()
{

}


int RegisterModel::rowCount(const QModelIndex &parent) const
{
    return RegisterDTO::getSize();
}


int RegisterModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


QVariant RegisterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    {
        return dto->getLine("reg", index.row());
    }
    case Qt::EditRole:
        return dto->getRegister(index.row()).toInt();
    default:
        return QVariant();
    }
}


QVariant RegisterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);

    if (orientation == Qt::Orientation::Vertical) {
        return "R[" + QString::number(section) + "]:";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}


Qt::ItemFlags RegisterModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        // Return to the user to interact with the interface
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}


bool RegisterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    switch (role) {
    case Qt::EditRole:{
        qDebug()<<value;
        RegisterDTO::changeRegister(index.row(), value.toInt(), "regData");
        dto->save();
        emit dataChanged(index, index);
        return true;
    }
    default:
        emit dataChanged(index, index);
        return true;
    }
    return true;
}


PoseRegisterModel::PoseRegisterModel(QObject *parent) : QAbstractTableModel(parent)
{
    dto = new RegisterDTO();
}


PoseRegisterModel::~PoseRegisterModel()
{
    delete dto;
}


void PoseRegisterModel::resetModel()
{

}


int PoseRegisterModel::rowCount(const QModelIndex &parent) const
{
    return RegisterDTO::getSize();
}


int PoseRegisterModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


QVariant PoseRegisterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    {
        return dto->getLine("poserReg", index.row());
    }
    case Qt::EditRole:
                return dto->getRawRegister(index.row());
    default:
        return QVariant();
    }
}

QVariant PoseRegisterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);

    if (orientation == Qt::Orientation::Vertical) {
        return "PR[" + QString::number(section) + "]:";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}



Qt::ItemFlags PoseRegisterModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        // Return to the user to interact with the interface
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}


bool PoseRegisterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    switch (role) {
    case Qt::EditRole:{
        qDebug()<<value;
        dto->mergeObject(index.row(), value.toJsonObject());
        dto->save();
        return true;
    }
    default:
        return true;
    }
    return true;
}
