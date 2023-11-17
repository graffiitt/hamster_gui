#include "execturtorwidget.h"
#include "ui_execturtorwidget.h"


ExecturtorWidget::ExecturtorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExecturtorWidget)
{
    ui->setupUi(this);
    exec = new IExecutor();

    programm = new Programm();
    prgModel = new ProgrammModel(programm);
    ui->tableView->setModel(prgModel);

    safety = Safety::getInstance();

    connect(exec, &IExecutor::updateModel, prgModel, &ProgrammModel::updateProgramm, Qt::DirectConnection);
    connect(safety, &Safety::changeCurrentLine, this, &ExecturtorWidget::changeCurrLine);
}


ExecturtorWidget::~ExecturtorWidget()
{
    delete ui;
    delete exec;
    delete prgModel;
    delete programm;
}

void ExecturtorWidget::updateLanguage()
{
    QLocale locale;
    QString path = QApplication::applicationDirPath();
    QString fileName = QString("/executor_%1.qm").arg(locale.name());

    qApp->removeTranslator(&translate);
    if (translate.load(path + fileName))
    {
        qApp->installTranslator(&translate);
    }
}

void ExecturtorWidget::on_runButton_clicked()
{
    exec->start();

}


void ExecturtorWidget::on_holdButton_clicked()
{
    exec->requestInterruption();

}


void ExecturtorWidget::on_openFileButton_clicked()
{
    ui->fileBox->clear();
    pathFolder = JSONmodule::getPathProgramms(this);
    progFiles = JSONmodule::getProgramms(pathFolder);
    ui->fileBox->addItems(progFiles);
}


void ExecturtorWidget::on_fileBox_activated(int index)
{
    exec->loadProgramm(pathFolder, progFiles.value(index));

    //    prgModel->updateProgramm(jsonLoad->openFile(path));
}


void ExecturtorWidget::on_tableView_clicked(const QModelIndex &index)
{

}


 
void ExecturtorWidget::changeCurrLine(int line)
{
    ui->tableView->selectRow(line);
}

void ExecturtorWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

void ExecturtorWidget::on_stepButton_clicked(bool checked)
{
    emit exec->setMode(checked);

}

