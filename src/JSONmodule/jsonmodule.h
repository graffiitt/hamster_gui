#ifndef JSONMODULE_H
#define JSONMODULE_H

#include <QJsonArray>

#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "jsonloader.h"
#include "../ICommand/icommand.h"
#include "../RegisterWidget/registerbase.h"

class JSONmodule: protected JSONloader
{
public:
    JSONmodule();
    ~JSONmodule();

    void createProgramm(QString path);
    QList<ICommand *> openFile(QString path);
    void saveFile(Programm *progamm, QString path);
    QList<RegisterBase *> openFile(QString path, QString type);
    void saveFile(Registers *reg, QString path);
    bool isExist(QString path);

    static QString getPathGUI(QWidget *parent);
    static QString getPathProgramms(QWidget *parent);
    static QStringList getProgramms(QString path);
};

#endif // JSONMODULE_H
