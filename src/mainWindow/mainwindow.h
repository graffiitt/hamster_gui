#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTranslator>
#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

#include "../ProgEditorWidget/programmeditorwidget.h"
#include "../stateWidget/safety.h"
#include "../ExectutorWidget/execturtorwidget.h"
#include "../RegisterWidget/registerwidget.h"
#include "../CommunicateWidget/communicatorwidget.h"
#include "../IOwidget/ioWidget.h"
#include "../moveEngine/MoveController.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_homeButton_pressed();
    void on_progButton_pressed();
    void on_regButton_pressed();
    void on_runButton_pressed();
    void on_ioButton_pressed();

    void on_createFileAction_triggered();
    void on_openFileAction_triggered();
    void on_saveAsFileAction_triggered();
    void on_motorContrlAction_triggered();
    void on_resetAction_triggered();
    void on_connectSTM_action_triggered();
    void on_saveAction_triggered();

    void changeEvent(QEvent *event);
    void checkFiles();
    void on_changeLanguageEnglish_triggered();
    void on_changeLanguageRussian_triggered();

private:
    QString _path, _pathProgramm, _pathRegisters;

    Ui::MainWindow *ui;
    ProgrammEditorWidget *programmWidget;
    StateWidget *stateWidget;
    Safety *safety;
    ExecturtorWidget *execWidget;
    RegisterWidget *regWidget;
    CommunicatorWidget *connectWidget;
    IOWidget *ioWidget;
    MoveController *moveController;

    QTranslator translate;
    QLocale locale;
    
    void loadLanguage();
};
#endif // MAINWINDOW_H
