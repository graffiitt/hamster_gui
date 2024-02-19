#ifndef ABSTRACTPATHGENERATOR_H
#define ABSTRACTPATHGENERATOR_H

#include "DescriptionPose.h"

class AbstractPathGenerator
{
public:
    // AbstractPathGenerator();
    virtual ~AbstractPathGenerator(){};

    virtual void setCurrentPoint(int* currentPoint) = 0;
    virtual void setTargetPoint(int* targetPoint) = 0;
    virtual void setLimits(int acceleration, int speedLimit) = 0;
    virtual void computeTrajectory(Trajectory *trajectory) = 0;
};

#endif