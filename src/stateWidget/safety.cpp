#include "safety.h"

Safety* Safety::_instance = 0;


Safety::Safety()
{
    connect(this, &Safety::setError, this, &Safety::error, Qt::DirectConnection);
    connect(this, &Safety::resetErrors, this, &Safety::resetErr, Qt::DirectConnection);
    connect(this, &Safety::info, this, &Safety::informator);
    connect(this, &Safety::run, this, &Safety::setRun, Qt::DirectConnection);
    connect(this, &Safety::step, this, &Safety::setStep);
    connect(this, &Safety::changeCurrentLine, this, &Safety::showCurrentLine, Qt::DirectConnection);
    connect(this, &Safety::changeNameProg, this, &Safety::setName);
    connect(this, &Safety::setIO, this, &Safety::changeIO);
    connect(this, &Safety::setMCU, this, &Safety::changeMCU);
    connect(this, &Safety::setMode, this, &Safety::setModeMove);

}


Safety *Safety::getInstance()
{
    if (!_instance) {
        _instance = new Safety();
    }
    return _instance;
}


void Safety::informator(QString info)
{
    this->setInfo(info);
}


void Safety::error(QString info)
{
    this->StateWidget::setError(true);
    this->informator(info);
    emit outError(StateWidget::getStateError());
}


void Safety::resetErr()
{
    this->informator("errors reset");
    this->StateWidget::setError(false);
    emit outError(StateWidget::getStateError());
}


void Safety::setRun(bool state)
{
    this->setRunIcon(state);
}

void Safety::setStep(bool mode)
{
    this->setStepMode(mode);
}

void Safety::showCurrentLine(int line)
{
    this->setCurrentLine(line);
}

void Safety::setName(QString name)
{
    StateWidget::setOpenProg(name);
}

void Safety::changeIO(bool state)
{
    StateWidget::setIOicon(state);
}

void Safety::changeMCU(bool state)
{
    StateWidget::setMCUicon(state);
}

void Safety::setModeMove(ModeMove mode)
{
    switch (mode) {
    case ModeMove::automatic:
    case ModeMove::handle_1:
    case ModeMove::handle_2:
        break;
    }
}
