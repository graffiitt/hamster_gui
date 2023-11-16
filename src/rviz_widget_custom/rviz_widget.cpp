#include "rviz_widget.h"
#include "./ui_rviz_widget.h"

RVIZ_widget::RVIZ_widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RVIZ_widget)
{
    ui->setupUi(this);

    _rvizBase = new RVIZ_widget_base();
    ui->rv_frame->addWidget(_rvizBase);
    _rvizBase->initialize("");
}

RVIZ_widget::~RVIZ_widget()
{
    delete ui;
    delete _rvizBase;
}

void RVIZ_widget::on_addPanelButton_pressed()
{
    _rvizBase->openNewPanelDialog();
}

void RVIZ_widget::updateLanguage()
{
    QLocale locale;
    QString path = QApplication::applicationDirPath();
    QString fileName = QString("/rviz_widget_%1.qm").arg(locale.name());

    qApp->removeTranslator(&translate);
    if (translate.load(path + fileName))
    {
        qApp->installTranslator(&translate);
    }
}

void RVIZ_widget::on_saveButton_pressed()
{
    _rvizBase->saveConfig();
}

void RVIZ_widget::changeEvent(QEvent *event)
{
 if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
