#ifndef PATHGENERATORJOINT_H
#define PATHGENERATORJOINT_H

#include "AbstractPathGenerator.h"

class PathGeneratorJoint : public AbstractPathGenerator
{
private:
    int _limitSpeed;
    int _limitAcc;
    int* _targetPoint;
    int* _currentPoint;

public:
    void setCurrentPoint(int* currentPoint);
    void setTargetPoint(int* targetPoint);
    void setLimits(int acceleration, int speedLimit);
    void computeTrajectory(Trajectory *trajectory);
};

#endif
