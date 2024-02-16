#include "PathGeneratorJoint.h"

void PathGeneratorJoint::setCurrentPoint(Pose point)
{
    this->_currentPoint = &point;
}

void PathGeneratorJoint::setTargetPoint(Pose point)
{
    this->_targetPoint = &point;
}

void PathGeneratorJoint::setLimits(int acceleration, int speedLimit)
{
    this->_limitAcc = acceleration;
    this->_limitSpeed = speedLimit;
}

void PathGeneratorJoint::computeTrajectory(Trajectory *trajectory)
{
    qDebug() << "genjoint  compute";
}
