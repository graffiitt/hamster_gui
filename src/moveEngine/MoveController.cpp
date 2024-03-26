#include "MoveController.h"
#include "ui_MoveController.h"

MoveController::MoveController(QWidget *parent)
    : QDialog(parent), ui(new Ui::MoveController)
{
    ui->setupUi(this);
}

MoveController::~MoveController()
{
   delete ui;
}