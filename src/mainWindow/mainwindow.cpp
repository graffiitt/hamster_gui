#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    safety = Safety::getInstance();
    ui->infoLayout->addWidget(safety);

    programmWidget = new ProgrammEditorWidget();
    ui->editProgrammLayout->addWidget(programmWidget);

    regWidget = new RegisterWidget();
    ui->registerLayout->addWidget(regWidget);

    execWidget = new ExecturtorWidget();
    ui->executorLayout->addWidget(execWidget);

    connectWidget = new CommunicatorWidget();
    rviz_widget = new RVIZ_widget();
    ui->rviz_layout->addWidget(rviz_widget);

    ioWidget = new IOWidget();
    ui->ioLayout->addWidget(ioWidget);

    _path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
            "/GraffitRobotics";
    _pathProgramm = _path + "/default.json";
    _pathRegisters = _path + "/register.json";
    programmWidget->openProgramm(_pathProgramm);

    this->on_changeLanguageRussian_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete programmWidget;
    delete regWidget;
    delete execWidget;
    delete safety;
    delete connectWidget;
    delete rviz_widget;
    delete ioWidget;
}

void MainWindow::on_homeButton_pressed()
{
    if (ui->viewerWidget->currentIndex() != 0)
    {
        ui->viewerWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_progButton_pressed()
{
    if (ui->viewerWidget->currentIndex() != 1)
        ui->viewerWidget->setCurrentIndex(1);
}

void MainWindow::on_regButton_pressed()
{
    if (ui->viewerWidget->currentIndex() != 3)
    {
        ui->viewerWidget->setCurrentIndex(3);
    }
}

void MainWindow::on_runButton_pressed()
{
    if (ui->viewerWidget->currentIndex() != 2)
    {
        ui->viewerWidget->setCurrentIndex(2);
    }
}

void MainWindow::on_ioButton_pressed()
{
    if (ui->viewerWidget->currentIndex() != 4)
    {
        ui->viewerWidget->setCurrentIndex(4);
    }
}

void MainWindow::on_createFileAction_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "create programm",
                                                _path + "/programms",
                                                "*.prg");
    if (!path.isEmpty())
    {
        if (!path.endsWith(".prg"))
        {
            path = path + ".prg";
        }
        _pathProgramm = path;
        qDebug() << "mainwindow save as file" + path;
        programmWidget->createNewProgramm(_pathProgramm);
    }
}

void MainWindow::on_openFileAction_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "open programm",
                                                _path, "*.prg ;; *.json");
    if (!path.isEmpty())
    {
        if (!path.endsWith(".prg"))
        {
            path = path + ".prg";
        }
        _pathProgramm = path;
        programmWidget->openProgramm(_pathProgramm);
    }
}

void MainWindow::on_saveAsFileAction_triggered()
{

    QString path = QFileDialog::getSaveFileName(this, "save as programm",
                                                _path, tr("programm(*.prg)"));

    if (!path.isEmpty())
    {
        if (!path.endsWith(".prg"))
        {
            path = path + ".prg";
        }
        _pathProgramm = path;
        programmWidget->saveProgramm(_pathProgramm);
        programmWidget->openProgramm(_pathProgramm);
    }
}

void MainWindow::on_motorContrlAction_triggered()
{
}

void MainWindow::on_resetAction_triggered()
{
    safety->resetErrors();
}

void MainWindow::on_connectSTM_action_triggered()
{
    connectWidget->show();
}

void MainWindow::on_saveAction_triggered()
{
    programmWidget->saveProgramm(_pathProgramm);
}

void MainWindow::checkFiles()
{
    // check files in jsonModel
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        QLocale locale;
        ui->retranslateUi(this);
    }
}

void MainWindow::on_changeLanguageEnglish_triggered()
{
    locale = QLocale("en_US");
    QLocale::setDefault(locale);

    this->loadLanguage();
}

void MainWindow::on_changeLanguageRussian_triggered()
{
    locale = QLocale("ru_RU");
    QLocale::setDefault(locale);
    this->loadLanguage();
}

void MainWindow::loadLanguage()
{
    QString path = QApplication::applicationDirPath();
    QString fileName = QString("/mainWindow_%1.qm").arg(locale.name());

    qApp->removeTranslator(&translate);
    if (translate.load(path + fileName))
    {
        qApp->installTranslator(&translate);
    }
    programmWidget->updateLanguage();
    execWidget->updateLanguage();
    rviz_widget->updateLanguage();
}
