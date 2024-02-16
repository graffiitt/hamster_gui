#ifndef POSE_H
#define POSE_H

#include <qDebug>
#include <QList>
#include <QJsonObject>


enum CoordType
{
    joint,
    cartesian
};

// description joint state robot in point
class DescriptionPointJoint
{
public:
    float joint_1;
    float joint_2;
    float joint_3;
    float joint_4;
};

// description cartesian state robot in point
class DescriptionPointCartesian
{
public:
    int x;
    int y;
    int z;
    int a;
};

// description point velocity acceleration
class Pose
{
public:
    int speed;
    DescriptionPointJoint pointJoint;
    DescriptionPointCartesian pointCartesian;
};

// controller for description pose
// convert path
class Trajectory
{
private:
    QList<Pose *> _points;
    Pose _targetPoint;

public:
    ~Trajectory();

    bool setTargetPoint(QJsonObject obj);
    Pose getTargetPoint();
    void addPoint(Pose *point);
    Pose getPoint(int number);
    int getCountPoints();
};

#endif