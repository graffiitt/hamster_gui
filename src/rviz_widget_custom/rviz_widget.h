#ifndef RVIZ_WIDGET_H
#define RVIZ_WIDGET_H

#include <QWidget>
#include "rviz_widget_base.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class RVIZ_widget;
}
QT_END_NAMESPACE

class RVIZ_widget : public QWidget
{
    Q_OBJECT

public:
    RVIZ_widget(QWidget *parent = nullptr);
    ~RVIZ_widget();

private slots:
    void on_addPanelButton_pressed();

private:
    Ui::RVIZ_widget *ui;
    RVIZ_widget_base *_rvizBase;
};
#endif // RVIZ_WIDGET_H
