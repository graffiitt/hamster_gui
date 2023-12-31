#include "rviz_widget_base.h"

RVIZ_widget_base::RVIZ_widget_base(QWidget *parent)
    : QMainWindow(parent)
{
    _panelFactory = new PanelFactory();

    pakagePath = ros::package::getPath("hamster_gui");
    defoult_config_file = QString::fromStdString(pakagePath + "/config/default.rviz");
    safety = Safety::getInstance();
}

RVIZ_widget_base::~RVIZ_widget_base()
{
    delete _rvizManager;
    delete _rvizPanel;
    delete _panelFactory;
    for (int i = 0; i < _customPanels.size(); i++)
    {
        delete _customPanels[i].dock;
    }
}

void RVIZ_widget_base::initialize(const QString &display_config_file)
{

    if (!ros::isInitialized())
    {
        int argc = 0;
        ros::init(argc, 0, "rviz", ros::init_options::AnonymousName);
    }

    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    // add left button
    hide_left_button = new QToolButton();
    hide_left_button->setContentsMargins(0, 0, 0, 0);
    hide_left_button->setArrowType(Qt::LeftArrow);
    hide_left_button->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
    hide_left_button->setFixedWidth(16);
    hide_left_button->setAutoRaise(true);
    hide_left_button->setCheckable(true);
    connect(hide_left_button, &QToolButton::toggled, this, &RVIZ_widget_base::hideLeftDock);

    _rvizPanel = new RenderPanel(centralWidget);

    _rvizManager = new VisualizationManager(_rvizPanel, this);
    _rvizPanel->initialize(_rvizManager->getSceneManager(), _rvizManager);
    _rvizManager->initialize();

    if (display_config_file != "")
    {
        this->loadConfig(display_config_file);
    }
    else
    {
        this->loadConfig(defoult_config_file);
    }
    centralLayout->addWidget(hide_left_button, 0);
    centralLayout->addWidget(_rvizPanel, 1);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    _rvizManager->startUpdate();
}

void RVIZ_widget_base::openNewPanelDialog()
{
    QString classId;
    QString displayName;
    QStringList empty;

    NewObjectDialog *dialog = new NewObjectDialog(_panelFactory,
                                                  "Panel",
                                                  empty,
                                                  empty,
                                                  &classId,
                                                  &displayName,
                                                  this);
    _rvizManager->stopUpdate();
    if (dialog->exec() == QDialog::Accepted)
    {
        addPanelByName(displayName, classId);
    }
    _rvizManager->startUpdate();
}

void RVIZ_widget_base::saveConfig()
{
    Config config;
    save(config);

    YamlConfigWriter writer;
    writer.writeFile(config, display_config_file);
    if (writer.error())
    {
        ROS_ERROR("%s", qPrintable(writer.errorMessage()));
        safety->setError(writer.errorMessage());
    }
}

void RVIZ_widget_base::loadConfig(const QString &path)
{
    this->display_config_file = path;

    YamlConfigReader reader;
    Config config;

    reader.readFile(config, path);
    // load from config
    _rvizManager->load(config.mapGetChild("Visualization Manager"));
    this->loadPanels(config.mapGetChild("Panels"));
    config = config.mapGetChild("Window Geometry");
    QString main_window_config;
    if (config.mapGetString("QMainWindow State", &main_window_config))
    {
        restoreState(QByteArray::fromHex(qPrintable(main_window_config)));
    }
}

void RVIZ_widget_base::onDockPanelVisiblityChange(bool state)
{
    if (state)
    {
        QDockWidget *dock_widget = dynamic_cast<QDockWidget *>(sender());
        if (dock_widget)
        {
            Qt::DockWidgetArea area = dockWidgetArea(dock_widget);
            if (area == Qt::LeftDockWidgetArea)
            {
                hide_left_button->setChecked(false);
            }
            if (area == Qt::RightDockWidgetArea)
            {
            }
        }
    }
}

void RVIZ_widget_base::save(Config config)
{
    _rvizManager->save(config.mapMakeChild("Visualization Manager"));
    savePanels(config.mapMakeChild("Panels"));
    // saveWindowGeometry(config.mapMakeChild("Window Geometry"));
    config = config.mapMakeChild("Window Geometry");
    QByteArray windowState = saveState().toHex();
    config.mapSetValue("QMainWindow State", windowState.constData());

    QList<PanelDockWidget *> dockWidget = findChildren<PanelDockWidget *>();
    for (QList<PanelDockWidget *>::iterator it = dockWidget.begin(); it != dockWidget.end(); it++)
    {
        (*it)->save(config.mapGetChild((*it)->windowTitle()));
    }
}

QWidget *RVIZ_widget_base::getParentWindow()
{
    return this;
}

PanelDockWidget *RVIZ_widget_base::addPane(const QString &name, QWidget *pane, Qt::DockWidgetArea area, bool floating)
{
    PanelDockWidget *dock;
    dock = new PanelDockWidget(name);
    dock->setContentWidget(pane);
    dock->setFloating(floating);
    dock->setObjectName(name);
    addDockWidget(area, dock);

    connect(dock, &PanelDockWidget::visibilityChanged, this, &RVIZ_widget_base::onDockPanelVisiblityChange);
    return dock;
}

QDockWidget *RVIZ_widget_base::addPanelByName(const QString &name, const QString &class_id, Qt::DockWidgetArea area, bool floating)
{
    QString error;
    Panel *panel = _panelFactory->make(class_id, &error);

    if (!panel)
    {
        panel = new FailedPanel(class_id, error);
    }
    panel->setName(name);
    PanelRecord record;
    record.dock = this->addPane(name, panel, area, floating);
    record.panel = panel;

    _customPanels.append(record);
    record.panel->initialize(_rvizManager);
    record.dock->setIcon(_panelFactory->getIcon(class_id));
    return record.dock;
}

void RVIZ_widget_base::loadPanels(const Config &config)
{
    for (int i = 0; i < _customPanels.size(); i++)
    {
        delete _customPanels[i].dock;
    }
    _customPanels.clear();

    int numPanels = config.listLength();
    for (int i = 0; i < numPanels; i++)
    {
        Config panelConfig = config.listChildAt(i);
        QString classId, name;
        if (panelConfig.mapGetString("Class", &classId) &&
            panelConfig.mapGetString("Name", &name))
        {
            QDockWidget *dock = this->addPanelByName(name, classId);
            if (dock)
            {
                Panel *panel = qobject_cast<Panel *>(dock->widget());
                if (panel)
                {
                    panel->load(panelConfig);
                }
            }
        }
    }
}

void RVIZ_widget_base::savePanels(Config config)
{
    config.setType(Config::List);
    for (int i = 0; i < _customPanels.size(); i++)
    {
        _customPanels[i].panel->save(config.listAppendNew());
    }
}

void RVIZ_widget_base::hideDockImpl(Qt::DockWidgetArea area, bool hide)
{
    QList<PanelDockWidget *> dockWidget = findChildren<PanelDockWidget *>();
    for (QList<PanelDockWidget *>::iterator it = dockWidget.begin(); it != dockWidget.end(); it++)
    {
        Qt::DockWidgetArea currArea = dockWidgetArea(*it);
        if (area == currArea)
        {
            (*it)->setCollapsed(hide);
        }
        if (hide)
        {
            (*it)->setAllowedAreas((*it)->allowedAreas() & ~area);
        }
        else
        {
            (*it)->setAllowedAreas((*it)->allowedAreas() | area);
        }
    }
}

void RVIZ_widget_base::hideLeftDock(bool hide)
{
    this->hideDockImpl(Qt::LeftDockWidgetArea, hide);
    hide_left_button->setArrowType(hide ? Qt::RightArrow : Qt::LeftArrow);
}

void RVIZ_widget_base::setStatus(const QString &message)
{
    emit statusUpdate(message);
}