#include "PathGeneratorLine.h"

void PathGeneratorLine::setCurrentPoint(Pose point)
{
    this->_currentPoint = &point;
}

void PathGeneratorLine::setTargetPoint(Pose point)
{
    this->_targetPoint = &point;
}

void PathGeneratorLine::setLimits(int acceleration, int speedLimit)
{
    this->_limitAcc = acceleration;
    this->_limitSpeed = speedLimit;
}

void PathGeneratorLine::computeTrajectory(Trajectory *trajectory)
{
    qDebug() << "genline compute";
}
