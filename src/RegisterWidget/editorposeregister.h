#ifndef EDITORPOSEREGISTER_H
#define EDITORPOSEREGISTER_H

#include <QWidget>
#include <QJsonObject>
#include <QDebug>


namespace Ui {
class EditorPoseRegister;
}

class EditorPoseRegister : public QWidget
{
    Q_OBJECT

public:
    explicit EditorPoseRegister(QWidget *parent = nullptr);
    ~EditorPoseRegister();

    void setItems(QJsonObject data);
    QJsonObject getItems();

private:
    Ui::EditorPoseRegister *ui;
};

#endif // EDITORPOSEREGISTER_H
