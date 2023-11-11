#include "iexecutor.h"


IExecutor::IExecutor()
{
    regDTO = new RegisterDTO();
    jsonLoad = new JSONmodule();
    safety = Safety::getInstance();

    _currentLine = 0;
    errorState = stepMode = stepTrig = false;

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
    programm = jsonLoad->openFile(pathFolder+"/"+ProgName);

    listProgram.clear();lineProgramm.clear();
    listProgram.push_back(ProgName);

    emit updateModel(programm);

    qDebug()<< "iexec " << lineProgramm<< "  "<< listProgram;
}


void IExecutor::execCall(QJsonObject obj)
{
    Q_UNUSED(obj);
    QString progName = programm.at(_currentLine)->getData()["namePrg"].toString();
    QString path = pathFolder + "/" + progName;

    if(jsonLoad->isExist(path))
    {
        qDebug()<<"change prog";
        programm = jsonLoad->openFile(path);
        emit updateModel(programm);

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
    switch (obj["operator"].toInt()) {
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
        if(this->getNumber(2, obj) != 0)
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
    switch (obj["regOutType"].toInt()) {
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
    switch (obj["itemType_"+QString::number(num)].toInt()) {
    case TypeItem::number:
    {
        out = obj["number_"+QString::number(num)].toInt();
        break;
    }
    case TypeItem::reg:
    {
        int val = obj["register_"+QString::number(num)].toInt();
        out = regDTO->getRegister(val).toInt();
        break;
    }
    case TypeItem::posReg:
    {
        int val = obj["poseReg_"+QString::number(num)].toInt();
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

}


void IExecutor::execJump(QJsonObject obj)
{
    if(programm.at(_currentLine)->getData()["mode"].toInt() == JumpMode::jump)
        for ( int i = 0; i < programm.size(); i++)
        {
            if ( programm.at(i)->getType() == "jump" &&
                 programm.at(i)->getData()["mode"].toInt() == JumpMode::lbl &&
                 programm.at(i)->getData()["lbl"].toInt() == obj["lbl"].toInt())
            {
                _currentLine = i;
                i = programm.size();
            }
        }
}


void IExecutor::execPoint(QJsonObject obj)
{

}


void IExecutor::execWait(QJsonObject obj)
{
    switch (obj["waitType"].toInt()) {
    case WaitType::timer: // time
    {
        QTime timer = QTime::currentTime().addSecs(obj["time"].toInt());
        while(QTime::currentTime()<timer && !errorState && !this->isInterruptionRequested())
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
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


void IExecutor::errorSlot(bool state)
{
    errorState = state;
}


void IExecutor::run()
{
    qDebug()<<"exec start err "<< errorState << "stpe "<< stepTrig;
    safety->run(true);
    stepTrig = true;

    while(!errorState && stepTrig && programm.size() != _currentLine  && !this->isInterruptionRequested())
    {
        QJsonObject obj = programm.at(_currentLine)->getData();

        safety->changeCurrentLine(_currentLine);
        switch (programm.at(_currentLine)->getId()) {
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
            break;
        }
        case Command::Jump:
        {
            this->execJump(obj);
            break;
        }
        case Command::Point:
        {
            break;
        }
        case Command::Wait:
        {
            this->execWait(obj);
            break;
        }
        }

        if (programm.size() == _currentLine + 1 )
        {
            if (listProgram.size() != 1)
            {
                qDebug()<<"change prog";

                _currentLine = lineProgramm.takeLast() + 1;
                listProgram.removeLast();
                programm = jsonLoad->openFile(pathFolder + "/" + listProgram.last());
                emit updateModel(programm);
                safety->changeCurrentLine(_currentLine);

            }
            else
            {
                _currentLine = -1;
                qDebug()<<"exec break";
                stepTrig = false;
                //this->requestInterruption();
                qDebug()<<"stop requset";
            }
        }

        if(stepMode)
        {
            stepTrig = false;
        }

        _currentLine++;
    }
    safety->run(false);
    qDebug()<<"exec stop";
}


void IExecutor::changeMode(bool stepMode)
{
    this->stepMode = stepMode;
    safety->step(stepMode);
}
