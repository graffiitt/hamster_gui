#include "mainwindow.h"

#include <ros/ros.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    if (!ros::isInitialized())
    {
        ros::init(argc, argv, "rviz_custom_widget", ros::init_options::AnonymousName);
    }
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
