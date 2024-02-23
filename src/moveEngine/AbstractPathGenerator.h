#ifndef ABSTRACTPATHGENERATOR_H
#define ABSTRACTPATHGENERATOR_H

#include "DescriptionPose.h"

class AbstractPathGenerator
{
public:
    // AbstractPathGenerator();
    virtual ~AbstractPathGenerator(){};

    virtual void setCurrentPoint(float* currentPoint) = 0;
    virtual void setTargetPoint(float* targetPoint) = 0;
    virtual void setLimits(float acceleration, float speedLimit) = 0;
    virtual void computeTrajectory(Trajectory *trajectory) = 0;
};

#endif