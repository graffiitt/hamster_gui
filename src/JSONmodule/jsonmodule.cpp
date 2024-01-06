#include "jsonmodule.h"


JSONmodule::JSONmodule()
{

}


JSONmodule::~JSONmodule()
{
}


void JSONmodule::createProgramm(QString path)
{
    this->save(path, "programm", QJsonArray());
}


QList<ICommand *> JSONmodule::openFile(QString path)
{
    QJsonObject jsonObj = this->read(path);

    Programm programm;
    QJsonArray _data;

    if (jsonObj.contains("programm"))
    {
        _data = jsonObj["programm"].toArray();

        foreach(const QJsonValue &v, _data)
        {
            QJsonObject obj = v.toObject();

            switch (obj.value("id").toInt())
            {
            case Command::Point:
            {

                MoveCommand *cmd = new MoveCommand();
                cmd->setData(obj["description"].toObject());
                programm.append(cmd);
                break;
            }

            case Command::Empty:
            {
                EmptyCommand *empt = new EmptyCommand();
                programm.append(empt);
                break;
            }
            case Command::Comment:
            {
                CommentCommand *comm = new CommentCommand();
                comm->setData(obj["description"].toObject());
                programm.append(comm);
                break;
            }
            case Command::Math:
            {
                MathCommand *math = new MathCommand();
                math->setData(obj["description"].toObject());
                programm.append(math);
                break;
            }
            case Command::Call:
            {
                CallCommand *callCmd = new CallCommand();
                callCmd->setData(obj["description"].toObject());
                programm.append(callCmd);
                break;
            }
            case Command::Wait:
            {
                WaitCommand  *wt = new WaitCommand();
                wt->setData(obj["description"].toObject());
                programm.append(wt);
                break;
            }
            case Command::Jump:
            {
                JumpCommand *jmp = new JumpCommand();
                jmp->setData(obj["description"].toObject());
                programm.append(jmp);
                break;
            }
            case Command::If:
            {
                IfCommand *ifCmd = new IfCommand();
                ifCmd->setData(obj["description"].toObject());
                programm.append(ifCmd);
                break;
            }
            case Command::Io:
                IoCommand *ioCmd = new IoCommand();
                ioCmd->setData(obj["description"].toObject());
                programm.append(ioCmd);
                break;
            }
        }
        JSONloader::changeName(path.split("/").back());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("document don't contains programm");
        msgBox.exec();
    }
    return programm;
}


void JSONmodule::saveFile(Programm *progamm, QString path)
{
    QJsonArray array;
    for (int i = 0; i < progamm->size(); i++)
        array.push_back(progamm->value(i)->getJSONobject());
    this->save(path, "programm", array);
}


QList<RegisterBase *> JSONmodule::openFile(QString path, QString type)
{
    Q_UNUSED(type);

    QJsonObject jsonObj = this->read(path);
    Registers reg;
    QJsonArray _data;
    if (jsonObj.contains("register"))
    {
        _data = jsonObj["register"].toArray();
        foreach(const QJsonValue &v, _data)
        {
            QJsonObject obj = v.toObject();
            RegisterBase *r = new RegisterBase();
            r->setData(obj);
            reg.append(r);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("error load register's data");
        msgBox.exec();
    }

    return reg;
}


void JSONmodule::saveFile(Registers *reg, QString path)
{
    QJsonArray array;
    for (int i = 0; i < reg->size(); i++)
        array.push_back(reg->value(i)->getData());
    this->save(path, "register", array);
}

bool JSONmodule::isExist(QString path)
{
    return QFile::exists(path);
}


QString JSONmodule::getPathGUI(QWidget *parent)
{
    QString str = QFileDialog::getOpenFileName(parent,
                                               "open programm",
                                               QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                                               "/GraffitRobotics" , "*.prg ;; *.json");

    return str.split("/").back();
}


QString JSONmodule::getPathProgramms(QWidget *parent)
{
    QString str = QFileDialog::getExistingDirectory(parent,
                                                    "open programm",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                                                    "/GraffitRobotics");
    return str;
}

QStringList JSONmodule::getProgramms(QString path)
{
    QDir directory(path);
    QStringList prg = directory.entryList(QStringList() << "*.json" << "*.prg",QDir::Files);
    return prg;
}


