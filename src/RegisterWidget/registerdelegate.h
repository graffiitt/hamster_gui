#ifndef REGISTERDELEGATE_H
#define REGISTERDELEGATE_H

#include <QStyledItemDelegate>
#include <QSpinBox>
#include "editorposeregister.h"


class RegisterDelegate: public QStyledItemDelegate
{

public:
    explicit RegisterDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;


};


class PoseRegisterDelegate: public QStyledItemDelegate
{

public:
    explicit PoseRegisterDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // REGISTERDELEGATE_H
