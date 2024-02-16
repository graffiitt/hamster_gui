#ifndef PATHGENERATORLINE_H
#define PATHGENERATORLINE_H

#include "AbstractPathGenerator.h"

class PathGeneratorLine : public AbstractPathGenerator
{
private:
    int _limitSpeed;
    int _limitAcc;
    Pose *_targetPoint;
    Pose *_currentPoint;

public:
    void setCurrentPoint(Pose point);
    void setTargetPoint(Pose point);
    void setLimits(int acceleration, int speedLimit);
    void computeTrajectory(Trajectory *trajectory);
};

#endif
