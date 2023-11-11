#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    _path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
            "/GraffitRobotics";
    _pathProgramm = _path + "/default.json";
    _pathRegisters = _path + "/register.json";
    programmWidget->openProgramm(_pathProgramm);
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
}


void MainWindow::on_homeButton_pressed()
{
    if(ui->viewerWidget->currentIndex() != 0)
    {
        ui->viewerWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_progButton_pressed()
{
    if(ui->viewerWidget->currentIndex() != 1)
        ui->viewerWidget->setCurrentIndex(1);
}


void MainWindow::on_regButton_pressed()
{
    if(ui->viewerWidget->currentIndex() != 3)
    {
        ui->viewerWidget->setCurrentIndex(3);

    }
}

void MainWindow::on_runButton_pressed()
{
    if(ui->viewerWidget->currentIndex() != 2)
    {
        ui->viewerWidget->setCurrentIndex(2);

    }
}


void MainWindow::on_createFileAction_triggered()
{
    _pathProgramm = QFileDialog::getSaveFileName(this,
                                                 "create programm",
                                                 _path +"/programms",
                                                 "*.prg ;; *.json");
    qDebug()<< "mainwindow save as file" + _pathProgramm;
    programmWidget->createNewProgramm(_pathProgramm);
}


void MainWindow::on_openFileAction_triggered()
{
    _pathProgramm = QFileDialog::getOpenFileName(this,
                                                 "open programm",
                                                 _path, "*.prg ;; *.json");
    programmWidget->openProgramm(_pathProgramm);
}


void MainWindow::on_saveAsFileAction_triggered()
{
    _pathProgramm = QFileDialog::getSaveFileName(this, "create programm",
                                                 _path, "*.prg ;; *.json");
    qDebug()<< "mainwindow save as file" + _pathProgramm;
    programmWidget->saveProgramm(_pathProgramm);
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
//    connectWidget->updateComPorts();
}


void MainWindow::on_saveAction_triggered()
{
programmWidget->saveProgramm(_pathProgramm);
}

void MainWindow::checkFiles()
{
    // check files in jsonModel
}

