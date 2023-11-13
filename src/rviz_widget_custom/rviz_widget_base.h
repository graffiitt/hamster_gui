#ifndef RVIZ_WIDGET_BASE_H
#define RVIZ_WIDGET_BASE_H

#include <fstream>

#include <QDebug>
#include <QMainWindow>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QToolButton>
#include <QPushButton>
#include <ros/ros.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>

#include <rviz/widget_geometry_change_detector.h>
#include <rviz/new_object_dialog.h>
#include <rviz/panel_factory.h>
#include <rviz/panel.h>
#include <rviz/config.h>
#include <rviz/failed_panel.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/visualization_manager.h>
#include <rviz/window_manager_interface.h>
#include <rviz/panel_dock_widget.h>
#include <rviz/yaml_config_reader.h>
#include <rviz/yaml_config_writer.h>

namespace fs = boost::filesystem;
using namespace rviz;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class RVIZ_widget_base;
}
QT_END_NAMESPACE

class RVIZ_widget_base : public QMainWindow, public WindowManagerInterface
{
    Q_OBJECT

public:
    RVIZ_widget_base(QWidget *parent = nullptr);
    ~RVIZ_widget_base();
    void initialize(const QString &display_config_file);
    void openNewPanelDialog();
    void loadConfig(const QString &path);
    void saveConfig();

signals:
    void statusUpdate(const QString &message);

private slots:
    virtual void setStatus(const QString &message);
    void onDockPanelVisiblityChange(bool state);

private:
    WidgetGeometryChangeDetector *_geom_change_detector;
    rviz::VisualizationManager *_rvizManager;
    rviz::RenderPanel *_rvizPanel;
    rviz::Display *_rvizDisplay;
    rviz::PanelFactory *_panelFactory;
    QToolButton *hide_left_button;
    QToolButton *hide_right_button;
    QString defoult_config_file;
    QString display_config_file;
    std::string pakagePath;

    struct PanelRecord
    {
        Panel *panel;
        PanelDockWidget *dock;
        QString name;
        QString classId;
        //   QAction *deleteAction;
    };
    QList<PanelRecord> _customPanels;

    virtual void save(Config config);
    virtual QWidget *getParentWindow();
    virtual PanelDockWidget *addPane(const QString &name,
                                     QWidget *pane,
                                     Qt::DockWidgetArea area = Qt::LeftDockWidgetArea,
                                     bool floating = false);
    QDockWidget *addPanelByName(const QString &name,
                                const QString &class_id,
                                Qt::DockWidgetArea area = Qt::LeftDockWidgetArea,
                                bool floating = true);
    void loadPanels(const Config &config);
    void savePanels(Config config);
    void hideDockImpl(Qt::DockWidgetArea area, bool hide);
    void hideLeftDock(bool hide);
};
#endif // RVIZ_WIDGET_H
