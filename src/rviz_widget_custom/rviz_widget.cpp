#include "rviz_widget.h"
#include "./ui_rviz_widget.h"

RVIZ_widget::RVIZ_widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RVIZ_widget)
{
    ui->setupUi(this);

    _rvizBase = new RVIZ_widget_base();
    ui->rv_frame->addWidget(_rvizBase);
    _rvizBase->initialize("");
    
}

RVIZ_widget::~RVIZ_widget()
{
    delete ui;
    delete _rvizBase;
}

void RVIZ_widget::on_addPanelButton_pressed()
{
_rvizBase->openNewPanelDialog();
}