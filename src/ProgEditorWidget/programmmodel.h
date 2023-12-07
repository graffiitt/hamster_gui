#ifndef PROGRAMMMODEL_H
#define PROGRAMMMODEL_H

#include <QAbstractItemView>
#include "../ICommand/icommand.h"

class ProgrammModel : public QAbstractTableModel
{
public:
    ProgrammModel(Programm *pr);

    void addComand(QModelIndex ind, ICommand *cmd);
    void deleteCommands();
    void deleteCommand(QModelIndex idx);

    Command getId(QModelIndex idx);
    bool isEmpty();
    QJsonValue getData(QModelIndex idx, QString key);
    void setData(QJsonValue data, QString key, Command id, QModelIndex idx);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void updateProgramm(QList<ICommand *> pr);

private:
    Programm *programm;
};

#endif // PROGRAMMMODEL_H
