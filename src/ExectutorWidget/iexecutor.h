#ifndef IEXECUTOR_H
#define IEXECUTOR_H

#include <QThread>
#include <QTime>
#include <QCoreApplication>

#include "../JSONmodule/jsonmodule.h"
#include "../RegisterWidget/registerdto.h"
#include "../IOwidget/ioWidget.h"
#include "../moveEngine/MoveEngine.h"

class IExecutor : public QThread
{
    Q_OBJECT
public:
    IExecutor();
    ~IExecutor();

    void loadProgramm(QString pathFolder, QString ProgName);
    void changeExecLine(int line);

private:
    Programm programm;
    JSONmodule *jsonLoad;
    Safety *safety;
    RegisterDTO *regDTO;

    int _currentLine;
    bool stepMode, stepTrig, errorState, updateTable;
    QString pathFolder;
    QList<QString> listProgram;
    QList<int> lineProgramm;

    virtual void run() override;
    void execCall(QJsonObject obj);
    void execMath(QJsonObject obj);
    int getNumber(int num, QJsonObject obj);
    void execIf(QJsonObject obj);
    bool compressionItem(QJsonObject num);
    void execJump(QJsonObject obj);
    int searchLBLtoJump(int lbl);
    void execPoint(QJsonObject obj);
    void execWait(QJsonObject obj);
    void execIO(QJsonObject obj);

public slots:
    void finishUpdateTable();

signals:
    void setMode(bool StepMode);

    void updateModel(QString path);

private slots:
    void errorSlot(bool state);
    void changeMode(bool stepMode);


};

#endif // IEXECUTOR_H
