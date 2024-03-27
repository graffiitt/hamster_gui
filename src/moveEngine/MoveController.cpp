#include "MoveController.h"
#include "ui_MoveController.h"

MoveController::MoveController(QWidget *parent)
    : QDialog(parent), ui(new Ui::MoveController)
{
    ui->setupUi(this);
    mcu = SerialTranslator::getInstance();
}

MoveController::~MoveController()
{
    delete ui;
}

void MoveController::show()
{
    activeWindow = true;
    this->QWidget::show();
}

bool MoveController::isActive()
{
    return activeWindow;
}

void MoveController::closeEvent(QCloseEvent *e)
{
    activeWindow = false;
}
