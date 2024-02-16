#include "DescriptionPose.h"

Trajectory::~Trajectory()
{
    for (int i = _points.size(); i > 0; i--)
        delete _points.takeAt(i - 1);
}

Pose Trajectory::getTargetPoint()
{
    return _targetPoint;
}

void Trajectory::addPoint(Pose *point)
{
    _points.append(point);
}

Pose Trajectory::getPoint(int number)
{
    return Pose();
}

int Trajectory::getCountPoints()
{
    return _points.size();
}

// set and check valid point
bool Trajectory::setTargetPoint(QJsonObject obj)
{
     qDebug()<<"target:";
     obj = obj["point"].toObject();
    if (obj["coordType"].toInt() == CoordType::joint)
    {
        qDebug()<<"joint "<< obj;
        _targetPoint.pointJoint.joint_1 = obj["j1"].toInt();
        _targetPoint.pointJoint.joint_2 = obj["j2"].toInt();
        _targetPoint.pointJoint.joint_3 = obj["j3"].toInt();
        _targetPoint.pointJoint.joint_4 = obj["j4"].toInt();
    }
    else if (obj["coordType"].toInt() == CoordType::cartesian)
    {
        qDebug()<<"cart "<< obj;
        _targetPoint.pointCartesian.x = obj["x"].toInt();
        _targetPoint.pointCartesian.y = obj["y"].toInt();
        _targetPoint.pointCartesian.z = obj["z"].toInt();
        _targetPoint.pointCartesian.a = obj["a"].toInt();
    }

    return false;
}
