#include "rviz_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{

  if (!ros::isInitialized())
  {
    ros::init(argc, argv, "rviz_custom_widget", ros::init_options::AnonymousName);
  }

  QApplication a(argc, argv);
  RVIZ_widget w;
  w.show();

  return a.exec();
}
