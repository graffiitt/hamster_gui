#include "rviz_widget.h"
#include "./ui_rviz_widget.h"


RVIZ_widget::RVIZ_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RVIZ_widget)
{
    ui->setupUi(this);
   // n = new ros::NodeHandle();
}

RVIZ_widget::~RVIZ_widget()
{
    delete ui;
   // delete n;
}


