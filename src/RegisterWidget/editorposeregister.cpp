#include "editorposeregister.h"
#include "ui_editorposeregister.h"

EditorPoseRegister::EditorPoseRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorPoseRegister)
{
    ui->setupUi(this);
}


EditorPoseRegister::~EditorPoseRegister()
{
    delete ui;
}


void EditorPoseRegister::setItems(QJsonObject data)
{
    ui->nameEdit->setText(data.value("regName").toString());
    ui->x_spinBox->setValue(data.value("poseRegItem_1").toInt());
    ui->y_spinBox->setValue(data.value("poseRegItem_2").toInt());
    ui->z_spinBox->setValue(data.value("poseRegItem_3").toInt());
    ui->q_spinBox->setValue(data.value("poseRegItem_4").toInt());
}


QJsonObject EditorPoseRegister::getItems()
{
    QJsonObject obj;

    obj["regName"] = ui->nameEdit->text();
    obj["poseRegItem_1"] = ui->x_spinBox->value();
    obj["poseRegItem_2"] = ui->y_spinBox->value();
    obj["poseRegItem_3"] = ui->z_spinBox->value();
    obj["poseRegItem_4"] = ui->q_spinBox->value();

    return obj;
}
