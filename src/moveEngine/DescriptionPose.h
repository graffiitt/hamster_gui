#ifndef POSE_H
#define POSE_H

#include <qDebug>
#include <QList>
#include <QJsonObject>
#include "../stateWidget/safety.h"

enum CoordType
{
    joint,
    cartesian
};

class Joint
{
    int speed;
    int angle;
};

// description point velocity acceleration
class PoseCartesian
{
public:
    int speedCartesian;
    int cartesian[4];
};

class DataBasePositions
{
public:
    QList<PoseCartesian *> cartesianPoints;
    QList<Joint *> joint1;
    QList<Joint *> joint2;
    QList<Joint *> joint3;
    QList<Joint *> joint4;
};

// controller for description pose
class Trajectory
{
private:
    int limitSpeed;
    int limitAcc;

    int _targetPoint[4];

public:
    DataBasePositions *dataPoints;

    Trajectory();
    ~Trajectory();

    int getAccLimit();
    int getSpeedLimit();
    
    bool setTargetPoint(QJsonObject obj);
    int *getTargetPoint();
};

#endif