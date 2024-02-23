#ifndef PATHGENERATORJOINT_H
#define PATHGENERATORJOINT_H

#include "AbstractPathGenerator.h"

class PathGeneratorJoint : public AbstractPathGenerator
{
private:
    float _limitSpeed;
    float _limitAcc;
    float* _targetPoint;
    float* _currentPoint;

    QList<Joint*> getFirtsPath(float dq);
    float getTimeTravel(QList<Joint*> joint);
    float calcVelocity(float dq, float time);
    float solveSpeed(float dq, float time);
    void recomputePath(QList<Joint*> *joint, float timeTravel, float dq);
    void calcDistance(QList<Joint *> *joint);

public:
    void setCurrentPoint(float* currentPoint);
    void setTargetPoint(float* targetPoint);
    void setLimits(float acceleration, float speedLimit);
    void computeTrajectory(Trajectory *trajectory);
};

#endif
