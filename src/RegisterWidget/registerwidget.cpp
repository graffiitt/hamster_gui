#include "registerwidget.h"
#include "ui_registerwidget.h"

RegisterWidget::RegisterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);

    delegateRegister = new RegisterDelegate();
    regModel = new RegisterModel();
    ui->registerView->setItemDelegate(delegateRegister);
    ui->registerView->setModel(regModel);

    delegatePoseRegister = new PoseRegisterDelegate();
    poseRegModel = new PoseRegisterModel();

    ui->poseRegisterView->setItemDelegate(delegatePoseRegister);
    ui->poseRegisterView->setModel(poseRegModel);
}


RegisterWidget::~RegisterWidget()
{
    delete ui;
    delete regModel;
    delete delegateRegister;
    delete poseRegModel;
    delete delegatePoseRegister;
}


void RegisterWidget::on_clearRegButton_clicked()
{
    regModel->resetModel();
}


void RegisterWidget::on_clearPoseRegButton_clicked()
{
    poseRegModel->resetModel();
}

