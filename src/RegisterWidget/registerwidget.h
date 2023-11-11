#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>

#include "registermodel.h"
#include "registerdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWidget; }
QT_END_NAMESPACE

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

private slots:
    void on_clearRegButton_clicked();
    void on_clearPoseRegButton_clicked();

private:
    Ui::RegisterWidget *ui;
    RegisterModel *regModel;
    RegisterDelegate *delegateRegister;
    PoseRegisterDelegate *delegatePoseRegister;
    PoseRegisterModel *poseRegModel;

};
#endif // REGISTERWIDGET_H
