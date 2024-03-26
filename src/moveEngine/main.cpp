
#include "PathGeneratorJoint.h"
#include "PathGeneratorLine.h"

#include "MoveEngine.h"

#include "MoveController.h"
#include <QApplication>

enum MoveType
{
    m_joint,
    m_linear,
};

enum TypePoint
{
    point,
    poseRegister
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MoveController w;
    w.show();
    
    
    QJsonObject _data;
    _data.insert("moveType", MoveType::m_joint);
    _data.insert("pointType", TypePoint::point);
    _data.insert("numberRegister", 0);
    _data.insert("speed", 50);
    _data.insert("acc", 50);

    QJsonObject point;
    point.insert("coordType", CoordType::joint);
    point.insert("j1", 0);
    point.insert("j2", 20);
    point.insert("j3", 30);
    point.insert("j4", 40);
    _data.insert("point", point);

    MoveEngine eng;
    eng.setPoint(_data);
    eng.execPoint();

 
    return a.exec();
}