#include "registerdelegate.h"


RegisterDelegate::RegisterDelegate(QObject *parent): QStyledItemDelegate(parent)
{
}


QWidget *RegisterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);

    QSpinBox *spBox = new QSpinBox(parent);
    spBox->setRange(-5000, 5000);
    spBox->setFrame(false);
    return spBox;
}


void RegisterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *box = static_cast<QSpinBox*>(editor);

    box->setValue(index.data(Qt::EditRole).toInt());
    QStyledItemDelegate::setEditorData(editor, index);
}


void RegisterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *box = static_cast<QSpinBox*>(editor);

    model->setData(index, box->value(), Qt::EditRole);
}

void RegisterDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QSpinBox *widget = static_cast<QSpinBox*>(editor);

    QRect r = option.rect;
    r.setSize(widget->sizeHint());
    widget->setGeometry(r);
}


PoseRegisterDelegate::PoseRegisterDelegate(QObject *parent): QStyledItemDelegate(parent)
{
}


QWidget *PoseRegisterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    EditorPoseRegister *editor = new EditorPoseRegister(parent);

    return editor;
}


void PoseRegisterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    EditorPoseRegister *widget = static_cast<EditorPoseRegister*>(editor);

    widget->setItems(index.data(Qt::EditRole).toJsonObject());
    QStyledItemDelegate::setEditorData(editor, index);
}


void PoseRegisterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EditorPoseRegister *widget = static_cast<EditorPoseRegister*>(editor);

    model->setData(index, widget->getItems());
}


void PoseRegisterDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    EditorPoseRegister *widget = static_cast<EditorPoseRegister*>(editor);
    QRect r = option.rect;
    r.setSize(widget->sizeHint());
    widget->setGeometry(r);
}
