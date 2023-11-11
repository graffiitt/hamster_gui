#include "jsonloader.h"

JSONloader::JSONloader()
{
    safety = Safety::getInstance();
}

void JSONloader::save(QString path, QString item, QJsonValue obj)
{
    QFile saveFile(path);
    if (saveFile.open(QIODevice::WriteOnly)) // на чтение
    {
        QJsonObject objectJson;
        objectJson[item] = obj;
        QJsonDocument saveDoc(objectJson);
        saveFile.write(saveDoc.toJson());
        saveFile.close();
    }
    else
    {
        qDebug() << "jsonloader file not save";
        emit safety->setError("file cannot be opened");
    }
}

QJsonObject JSONloader::read(QString path)
{
    QJsonObject jsonObj;

    if (QFile::exists(path) /*loadFile.exists()*/)
    {
        QFile loadFile(path);
        if (loadFile.open(QIODevice::ReadOnly))
        {
            QByteArray loadData = loadFile.readAll();
            loadFile.close();
            QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
            jsonObj = loadDoc.object();
        }
        else
        {
            emit safety->setError("file cannot be opened");
            qDebug() << " file cannot be opened";
        }
    }
    else
    {
        emit safety->setError("file not found");
    }
    return jsonObj;
}

void JSONloader::changeName(QString name)
{
    safety->changeNameProg(name);
}
