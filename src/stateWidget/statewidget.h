#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <qDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class StateWidget; }
QT_END_NAMESPACE

class StateWidget : public QWidget
{
    Q_OBJECT

public:
    StateWidget(QWidget *parent = nullptr);
    ~StateWidget();

    void setError(bool state);
    bool getStateError();
    void setInfo(QString msg);
    void setRunIcon(bool state);
    void setStepMode(bool state);
    void setCurrentLine(int line);
    void setOpenProg(QString name);
    void setIOicon(bool state);
    void setMCUicon(bool state);

private:
    const char *redColor = "background-color: #ff0000; color:#000000";
    const char *greenColor = "background-color: #00ff00; color:#000000";
    const char *yellowColor = "background-color: #ffff00; color:#000000";

    bool stateErr;

    Ui::StateWidget *ui;
};
#endif // STATEWIDGET_H
