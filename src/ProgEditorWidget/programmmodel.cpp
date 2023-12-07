#include "programmmodel.h"


ProgrammModel::ProgrammModel(Programm *pr) : programm(pr)
{
    beginResetModel();
    endResetModel();
}


void ProgrammModel::addComand(QModelIndex ind, ICommand *cmd)
{
    beginInsertRows(QModelIndex(),programm->size()-1,programm->size()-1);
    programm->insert(ind.row(), cmd);
    endInsertRows();
}


void ProgrammModel::updateProgramm(QList<ICommand *> pr)
{
    this->deleteCommands();
    beginInsertRows(QModelIndex(), 0, pr.size()-1);
    programm->append(pr);
    endInsertRows();
}


void ProgrammModel::deleteCommands()
{
    beginRemoveRows(QModelIndex(), 0,programm->size()-1);
    for(int i=programm->size(); i > 0; i--)
        delete programm->takeAt(i-1);
    endRemoveRows();
}


void ProgrammModel::deleteCommand(QModelIndex idx)
{
    if (idx.isValid() && programm->size() > idx.row())
    {
        beginRemoveRows(QModelIndex(), programm->size()-1,programm->size()-1);
        delete programm->takeAt(idx.row());
        endRemoveRows();
    }
}

Command ProgrammModel::getId(QModelIndex idx)
{
    return programm->value(idx.row())->getId();
}

bool ProgrammModel::isEmpty()
{
    return programm->isEmpty();
}

QJsonValue ProgrammModel::getData(QModelIndex idx, QString key)
{
    QJsonValue jv = programm->value(idx.row())->getData().value(key);
    return jv;
}


void ProgrammModel::setData(QJsonValue data, QString key, Command id, QModelIndex idx)
{
    if(idx.isValid() && programm->value(idx.row())->getId() == id)
    {
        QJsonObject obj;
        obj = programm->value(idx.row())->getData();
        obj[key] = data;
        programm->value(idx.row())->setData(obj);
        dataChanged(QModelIndex(), QModelIndex());
    }
}


int ProgrammModel::rowCount(const QModelIndex &parent) const
{
    return programm->size();
}


int ProgrammModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


bool ProgrammModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value);
    if (!index.isValid())
        return false;

    switch (role) {
    case Qt::EditRole:{
        emit dataChanged(index, index);
        return true;
    }
    default:
        return true;
    }
    return true;
}


QVariant ProgrammModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    {
        return programm->at(index.row())->getDescription();
    }
    default:
        return QVariant();
    }
}
