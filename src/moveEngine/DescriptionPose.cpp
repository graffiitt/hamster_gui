#include "DescriptionPose.h"

Trajectory::Trajectory()
{
    dataPoints = new DataBasePositions();
}

Trajectory::~Trajectory()
{
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
    qDebug() << "target:";
    obj = obj["point"].toObject();
    if (obj["coordType"].toInt() == CoordType::joint)
    {
        qDebug() << "joint " << obj;
        _targetPoint[0] = obj["j1"].toInt();
        _targetPoint[1] = obj["j2"].toInt();
        _targetPoint[2] = obj["j3"].toInt();
        _targetPoint[3] = obj["j4"].toInt();
    }
    else if (obj["coordType"].toInt() == CoordType::cartesian)
    {
        qDebug() << "cart " << obj;
        _targetPoint[0] = obj["x"].toInt();
        _targetPoint[1] = obj["y"].toInt();
        _targetPoint[2] = obj["z"].toInt();
        _targetPoint[3] = obj["a"].toInt();
    }

    return false;
}

float *Trajectory::getTargetPoint()
{
    return _targetPoint;
}
