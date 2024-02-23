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
public:
    Joint(){};
    Joint(float time, float speed)
    {
        this->time = time;
        this->speed = speed;
    };
    float time;
    float speed;
    float angle;
};

// description point velocity acceleration
class PoseCartesian
{
public:
    float time;
    float speedCartesian;
    float cartesian[4];
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
    float limitSpeed;
    float limitAcc;

    float _targetPoint[4];

public:
    DataBasePositions *dataPoints;

    Trajectory();
    ~Trajectory();

    float getAccLimit();
    float getSpeedLimit();
    bool setTargetPoint(QJsonObject obj);
    float *getTargetPoint();
};

#endif