#ifndef POSE_H
#define POSE_H

#include <qDebug>
#include <QList>
#include <QJsonObject>
#include "../stateWidget/safety.h"
#include "KinematicsSolver.h"

#ifndef MOVECOMMAND_H
enum CoordType
{
    joint,
    cartesian
};
#endif

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

// keep joint states and limits
class Trajectory
{
private:
    float limitSpeed;
    float limitAcc;
    float _targetPoint[4];

public:
    Trajectory();
    ~Trajectory();

    DataBasePositions *dataPoints;

    float getAccLimit();
    float getSpeedLimit();
    bool setTargetPoint(QJsonObject obj);
    float *getTargetPoint();
    void clearMemoryPoints();
};

#endif