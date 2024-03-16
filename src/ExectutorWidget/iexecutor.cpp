#include "iexecutor.h"

IExecutor::IExecutor()
{
    regDTO = new RegisterDTO();
    jsonLoad = new JSONmodule();
    safety = Safety::getInstance();

    _currentLine = 0;
    errorState = stepMode = stepTrig = updateTable = false;

    connect(this, &IExecutor::setMode, this, &IExecutor::changeMode, Qt::DirectConnection);
    connect(safety, &Safety::outError, this, &IExecutor::errorSlot, Qt::DirectConnection);
}

IExecutor::~IExecutor()
{
    delete regDTO;
    delete jsonLoad;
}

void IExecutor::loadProgramm(QString pathFolder, QString ProgName)
{
    this->pathFolder = pathFolder;
    programm = jsonLoad->openFile(pathFolder + "/" + ProgName);

    listProgram.clear();
    lineProgramm.clear();
    listProgram.push_back(ProgName);
    _currentLine = 0;
    emit updateModel(pathFolder + "/" + ProgName);

    while (!updateTable)
    {
    }
    updateTable = false;
    qDebug() << "iexec " << lineProgramm << "  " << listProgram;
}

void IExecutor::changeExecLine(int line)
{
    if (programm.size() > line)
        _currentLine = line;
}

void IExecutor::execCall(QJsonObject obj)
{
    Q_UNUSED(obj);
    QString progName = programm.at(_currentLine)->getData()["namePrg"].toString();
    QString path = pathFolder + "/" + progName;

    if (jsonLoad->isExist(path))
    {
        qDebug() << "change prog";
        programm = jsonLoad->openFile(path);
        emit updateModel(path);

        lineProgramm.push_back(_currentLine);
        listProgram.push_back(progName);

        _currentLine = -1;

        safety->changeCurrentLine(_currentLine + 1);
    }
    else
    {
        safety->setError("file " + progName + " not found");
    }
}

void IExecutor::execMath(QJsonObject obj)
{
    int outNum;
    switch (obj["operator"].toInt())
    {
    case MathOperator::none:
    {
        outNum = this->getNumber(1, obj);
        break;
    }
    case MathOperator::summ:
    {
        outNum = this->getNumber(1, obj) + this->getNumber(2, obj);
        break;
    }
    case MathOperator::minus:
    {
        outNum = this->getNumber(1, obj) - this->getNumber(2, obj);
        break;
    }
    case MathOperator::multiplication:
    {
        outNum = this->getNumber(1, obj) * this->getNumber(2, obj);
        break;
    }
    case MathOperator::divide:
    {
        if (this->getNumber(2, obj) != 0)
            outNum = this->getNumber(1, obj) / this->getNumber(2, obj);
        else
        {
            outNum = 0;
            safety->setError("divide by zero at line " + QString::number(_currentLine + 1));
        }
        break;
    }
    default:
        outNum = 0;
    }
    switch (obj["regOutType"].toInt())
    {
    case TypeItem::reg:
    {
        regDTO->changeRegister(obj["regOut"].toInt(), outNum, "regData");
        break;
    }
    case TypeItem::posReg:
    {
        QString key = "poseRegItem_" + QString::number(obj["poseRegItem"].toInt());
        regDTO->changeRegister(obj["poseReg"].toInt(), outNum, key);
        break;
    }
    }
    regDTO->save();
}

int IExecutor::getNumber(int num, QJsonObject obj)
{
    int out;
    switch (obj["itemType_" + QString::number(num)].toInt())
    {
    case TypeItem::number:
    {
        out = obj["number_" + QString::number(num)].toInt();
        break;
    }
    case TypeItem::reg:
    {
        int val = obj["register_" + QString::number(num)].toInt();
        out = regDTO->getRegister(val).toInt();
        break;
    }
    case TypeItem::posReg:
    {
        int val = obj["poseReg_" + QString::number(num)].toInt();
        int item = obj["poseRegItem_" + QString::number(num)].toInt();
        out = regDTO->getRawRegister(val)["poseRegItem_" + QString::number(item)].toInt();
        break;
    }
    default:
        out = 0;
    }

    return out;
}

void IExecutor::execIf(QJsonObject obj)
{
    bool compressionResult;
    if (obj["itemType_1"].toInt() == TypeItem::IO)
    {
        // requestMCU;
        bool IOstate = true;
        compressionResult = IOstate == obj[""].toBool();
    }
    else
        compressionResult = this->compressionItem(obj);

    if (compressionResult)
        _currentLine = this->searchLBLtoJump(obj["jumpLBL"].toInt());
}

bool IExecutor::compressionItem(QJsonObject num)
{
    switch (num["operator"].toInt())
    {
    case MathBehivor::equal:
    {
        return this->getNumber(1, num) == this->getNumber(2, num);
        break;
    }
    case MathBehivor::less:
    {
        return this->getNumber(1, num) < this->getNumber(2, num);

        break;
    }
    case MathBehivor::more:
    {
        return this->getNumber(1, num) > this->getNumber(2, num);

        break;
    }
    default:
        safety->setError("error compression");
        break;
    }
    return false;
}

void IExecutor::execJump(QJsonObject obj)
{
    if (programm.at(_currentLine)->getData()["mode"].toInt() == JumpMode::jump)
        _currentLine = this->searchLBLtoJump(obj["lbl"].toInt());
}

int IExecutor::searchLBLtoJump(int lbl)
{
    int line = 0;
    for (QList<ICommand *>::iterator it = programm.begin(); it != programm.end(); it++)
    {
        if ((*it)->getType() == "jump" &&
            (*it)->getData()["mode"].toInt() == JumpMode::lbl &&
            (*it)->getData()["lbl"].toInt() == lbl)
        {
            line = it - (programm.begin());
        }
    }
    return line;
}

void IExecutor::execPoint(QJsonObject obj)
{
    qDebug() << "exec point:\n"
             << obj;
    MoveEngine eng;
    eng.setPoint(obj);
    eng.execPoint();
}

/// @brief
/// переделать на eventloop
/// @param ref
void IExecutor::execWait(QJsonObject obj)
{
    switch (obj["waitType"].toInt())
    {
    case WaitType::timer: // time
    {
        QTime timer = QTime::currentTime().addSecs(obj["time"].toInt());
        while (QTime::currentTime() < timer && !errorState && !this->isInterruptionRequested())
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
        break;
    }
    case WaitType::ioHigh: // pinIn
    {

        break;
    }
    case WaitType::ioLow:
    {

        break;
    }
    }
}

void IExecutor::execIO(QJsonObject obj)
{
    switch (obj["type"].toInt())
    {
    case PINOUT::input:
    {
        break;
    }
    case PINOUT::output:
    {
        IOWidget::changePin(obj["pin"].toInt(), obj["state"].toBool());
        break;
    }
    }
}

void IExecutor::errorSlot(bool state)
{
    errorState = state;
}

void IExecutor::run()
{
    qDebug() << "exec start err " << errorState << "stpe " << stepTrig;
    safety->run(true);
    stepTrig = true;

    while (!errorState && stepTrig && programm.size() != _currentLine && !this->isInterruptionRequested())
    {
        QJsonObject obj = programm.at(_currentLine)->getData();
        safety->changeCurrentLine(_currentLine);
        switch (programm.at(_currentLine)->getId())
        {
        case Command::Call:
        {
            this->execCall(obj);
            break;
        }
        case Command::Math:
        {
            this->execMath(obj);
            break;
        }
        case Command::Comment:
        {
            safety->info(obj.value("data").toString());
            break;
        }
        case Command::Empty:
        {
            break;
        }
        case Command::If:
        {
            this->execIf(obj);
            break;
        }
        case Command::Jump:
        {
            this->execJump(obj);
            break;
        }
        case Command::Point:
        {
            this->execPoint(obj);
            break;
        }
        case Command::Wait:
        {
            this->execWait(obj);
            break;
        }
        case Command::Io:
        {
            this->execIO(obj);
            break;
        }
        }

        if (programm.size() == _currentLine + 1)
        {
            if (listProgram.size() != 1)
            {
                qDebug() << "change prog";

                _currentLine = lineProgramm.takeLast() + 1;
                listProgram.removeLast();
                programm = jsonLoad->openFile(pathFolder + "/" + listProgram.last());
                emit updateModel(pathFolder + "/" + listProgram.last());
                safety->changeCurrentLine(_currentLine);
            }
            else
            {
                _currentLine = -1;
                qDebug() << "exec break";
                stepTrig = false;
                qDebug() << "stop requset";
            }
        }

        if (stepMode)
        {
            stepTrig = false;
        }

        _currentLine++;
    }
    safety->run(false);
    qDebug() << "exec stop";
}

void IExecutor::changeMode(bool stepMode)
{
    this->stepMode = stepMode;
    safety->step(stepMode);
}

void IExecutor::finishUpdateTable()
{
    updateTable = true;
}
