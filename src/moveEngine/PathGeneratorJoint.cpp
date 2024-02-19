#include "PathGeneratorJoint.h"

void PathGeneratorJoint::setCurrentPoint(int* currentPoint)
{
    this->_currentPoint = currentPoint;
}

void PathGeneratorJoint::setTargetPoint(int* targetPoint)
{
    this->_targetPoint = targetPoint;
}

void PathGeneratorJoint::setLimits(int acceleration, int speedLimit)
{
    this->_limitAcc = acceleration;
    this->_limitSpeed = speedLimit;
}

void PathGeneratorJoint::computeTrajectory(Trajectory *trajectory)
{

    qDebug() << "genjoint  compute j3:"<< _targetPoint[2];
}
