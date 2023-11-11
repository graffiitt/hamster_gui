#ifndef REGISTERMODEL_H
#define REGISTERMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include "registerdto.h"


class RegisterModel : public QAbstractTableModel
{
public:
    explicit RegisterModel(QObject *parent = nullptr);
    ~RegisterModel();

    void resetModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    RegisterDTO *dto;

};


class PoseRegisterModel : public QAbstractTableModel
{

public:
    explicit PoseRegisterModel(QObject *parent = nullptr);
    ~PoseRegisterModel();

    void resetModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    RegisterDTO *dto;

};



#endif // REGISTERMODEL_H
