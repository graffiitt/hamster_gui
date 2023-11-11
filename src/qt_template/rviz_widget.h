#ifndef RVIZ_WIDGET_H
#define RVIZ_WIDGET_H

#include <QWidget>
#include <ros/ros.h>


QT_BEGIN_NAMESPACE
namespace Ui { class RVIZ_widget; }
QT_END_NAMESPACE

class RVIZ_widget : public QWidget
{
    Q_OBJECT

public:
    RVIZ_widget(QWidget *parent = nullptr);
    ~RVIZ_widget();

private:
    Ui::RVIZ_widget *ui;
        //ros::NodeHandle *n;
   ros::Publisher pub;
};
#endif // RVIZ_WIDGET_H
