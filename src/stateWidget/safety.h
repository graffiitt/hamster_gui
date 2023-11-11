#ifndef SAFETY_H
#define SAFETY_H

#include <QObject>
#include <QDebug>

#include "statewidget.h"

enum ModeMove{
    automatic,
    handle_1,
    handle_2
};

class Safety : public StateWidget
{
    Q_OBJECT
public:
    explicit Safety();
    static Safety* getInstance();

private:
    static Safety *_instance;

signals:
    void info(QString info);
    void setError(QString info);
    void outError(bool state);
    void resetErrors();
    void run(bool state);
    void step(bool mode);
    void changeCurrentLine(int line);
    void changeNameProg(QString name);
    void setIO(bool state);
    void setMCU(bool state);
    void setMode(ModeMove mode);

private slots:
    void informator(QString info);
    void error(QString info);
    void resetErr();
    void setRun(bool state);
    void setStep(bool mode);
    void showCurrentLine(int line);
    void setName(QString name);
    void changeIO(bool state);
    void changeMCU(bool state);
    void setModeMove(ModeMove mode);
};

#endif // SAFETY_H
