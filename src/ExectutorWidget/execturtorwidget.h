#ifndef EXECTURTORWIDGET_H
#define EXECTURTORWIDGET_H

#include <QDebug>

#include <QWidget>
#include <QTranslator>

#include "iexecutor.h"
#include "../ProgEditorWidget/programmmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ExecturtorWidget;
}
QT_END_NAMESPACE

class ExecturtorWidget : public QWidget
{
    Q_OBJECT
public:
    ExecturtorWidget(QWidget *parent = nullptr);
    ~ExecturtorWidget();

    void updateLanguage();

signals:
    void updateProgFinished();

private slots:
    void on_runButton_clicked();
    void on_holdButton_clicked();
    void on_openFileButton_clicked();
    void on_fileBox_activated(int index);
    void on_tableView_clicked(const QModelIndex &index);
    void on_stepButton_clicked(bool checked);

    void changeProgramm(QString path);
    void changeCurrLine(int line);

    void changeEvent(QEvent *event);

private:
    QStringList progFiles;
    QString pathFolder;
 
    Ui::ExecturtorWidget *ui;
    IExecutor *exec;
    Programm *programm;
    ProgrammModel *prgModel;
    Safety *safety;
    QTranslator translate;
};
#endif // EXECTURTORWIDGET_H
