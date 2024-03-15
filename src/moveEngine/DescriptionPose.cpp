#include "DescriptionPose.h"

Trajectory::Trajectory()
{
    dataPoints = new DataBasePositions();
}

Trajectory::~Trajectory()
{
    for (int i = dataPoints->cartesianPoints.size(); i > 0; i--)
        delete dataPoints->cartesianPoints.takeAt(i - 1);
    for (size_t i = dataPoints->joint1.size(); i > 0; i--)
        delete dataPoints->joint1.takeAt(i - 1);
    for (size_t i = dataPoints->joint2.size(); i > 0; i--)
        delete dataPoints->joint2.takeAt(i - 1);
    for (size_t i = dataPoints->joint3.size(); i > 0; i--)
        delete dataPoints->joint3.takeAt(i - 1);
    for (size_t i = dataPoints->joint4.size(); i > 0; i--)
        delete dataPoints->joint4.takeAt(i - 1);

    delete dataPoints;

    // for (int i = _points.size(); i > 0; i--)
    //     delete _points.takeAt(i - 1);
}

float Trajectory::getAccLimit()
{
    return limitAcc;
}

float Trajectory::getSpeedLimit()
{
    return limitSpeed;
}

// set and check valid point
bool Trajectory::setTargetPoint(QJsonObject obj)
{
    KinematicsSolver solverKin;
    obj = obj["point"].toObject();
    if (obj["coordType"].toInt() == CoordType::joint)
    {
        qDebug() << "joint " << obj;
        _targetPoint[0] = obj["j1"].toInt();
        _targetPoint[1] = obj["j2"].toInt();
        _targetPoint[2] = obj["j3"].toInt();
        _targetPoint[3] = obj["j4"].toInt();
        return solverKin.checkCoordJoint(_targetPoint);
    }
    else if (obj["coordType"].toInt() == CoordType::cartesian)
    {
        qDebug() << "cart " << obj;
        _targetPoint[0] = obj["x"].toInt();
        _targetPoint[1] = obj["y"].toInt();
        _targetPoint[2] = obj["z"].toInt();
        _targetPoint[3] = obj["a"].toInt();
        return solverKin.checkCoordCart(_targetPoint);
    }
    return false;
}

float *Trajectory::getTargetPoint()
{
    return _targetPoint;
}

void Trajectory::clearMemoryPoints()
{
    for (int i = dataPoints->cartesianPoints.size(); i > 0; i--)
        delete dataPoints->cartesianPoints.takeAt(i - 1);
    for (size_t i = dataPoints->joint1.size(); i > 0; i--)
        delete dataPoints->joint1.takeAt(i - 1);
    for (size_t i = dataPoints->joint2.size(); i > 0; i--)
        delete dataPoints->joint2.takeAt(i - 1);
    for (size_t i = dataPoints->joint3.size(); i > 0; i--)
        delete dataPoints->joint3.takeAt(i - 1);
    for (size_t i = dataPoints->joint4.size(); i > 0; i--)
        delete dataPoints->joint4.takeAt(i - 1);
}
