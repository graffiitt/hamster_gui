#ifndef PROGRAMMEDITORWIDGET_H
#define PROGRAMMEDITORWIDGET_H

#include <QTranslator>
#include <QWidget>
#include <QDebug>
#include "programmmodel.h"
#include "../JSONmodule/jsonmodule.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ProgrammEditorWidget;
}
QT_END_NAMESPACE

class ProgrammEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgrammEditorWidget(QWidget *parent = nullptr);
    ~ProgrammEditorWidget();

    void openProgramm(QString path);
    void createNewProgramm(QString path);
    void saveProgramm(QString path);

    void updateLanguage();

private slots:
    void on_moveButton_clicked();
    void on_logicButton_clicked();
    void on_mathButton_clicked();
    void on_addButton_clicked();
    void on_addLineButton_clicked();
    void on_deleteButton_clicked();
    void on_programmView_clicked(const QModelIndex &index);

    void on_commentButton_clicked();
    void on_commentLineEdit_textChanged(const QString &arg1);

    void on_regOutBox_currentIndexChanged(int index);
    void on_registerBox_valueChanged(int arg1);
    void on_registerBox_2_valueChanged(int arg1);
    void on_typeComboBox_2_activated(int index);
    void on_typeComboBox_1_activated(int index);

    void on_operatorComboBox_activated(int index);
    void on_firstNumBox_valueChanged(int arg1);
    void on_itemPoseReg_1_valueChanged(int arg1);
    void on_itemPoseReg_2_valueChanged(int arg1);
    void on_secondNumBox_valueChanged(int arg1);

    void on_callButton_clicked();

    void on_ifButton_clicked();
    void on_ifBeheviorBox_currentIndexChanged(int index);
    void on_ifItem_1_Box_currentIndexChanged(int index);
    void on_ifItem_2_Box_currentIndexChanged(int index);
    void on_ifItem_1_Spin_valueChanged(int arg1);
    void on_ifItem_2_Spin_valueChanged(int arg1);
    void on_ifItem_1_Spin_2_valueChanged(int arg1);
    void on_ifItem_2_Spin_2_valueChanged(int arg1);
    void on_iflLblBox_valueChanged(int arg1);
    void on_ifIOstate_stateChanged(int state);

    void on_ioButton_clicked();
    void on_ioComboBox_activated(int index);
    void on_ioSpinBox_valueChanged(int arg1);
    void on_ioCheckBox_stateChanged(int state);

    void on_waitButton_clicked();
    void on_waitBox_activated(int index);
    void on_waitSpinBox_valueChanged(int arg1);

    void on_lblButton_clicked();
    void on_lblSpinBox_valueChanged(int arg1);
    void on_lblComboBox_activated(int index);

    void changeEvent(QEvent *event);

private:
    Ui::ProgrammEditorWidget *ui;
    ProgrammModel *programmModel;

    Programm *programm;
    JSONmodule *jsonLoad;

    EmptyCommand *emptyCmd;
    CommentCommand *commentCmd;
    MathCommand *mathCmd;
    CallCommand *callCmd;
    JumpCommand *jmpCmd;
    WaitCommand *waitCmd;
    MoveCommand *moveCmd;
    IfCommand *ifCmd;
    IoCommand *ioCmd;

    QTranslator translate;

    void updateUIMathReg(QModelIndex index);
    void updateUINumbers(QModelIndex index);
    void updateRegItem(int arg1, int number, Command id);
};
#endif // PROGRAMMEDITORWIDGET_H
