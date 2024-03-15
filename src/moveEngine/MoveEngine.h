#ifndef MOVEENGINE_H
#define MOVEENGINE_H

#include "DescriptionPose.h"
#include "../CommunicateWidget/serialtranslator.h"
#include "PathGeneratorJoint.h"
#include "PathGeneratorJoint.h"

class MoveEngine
{
public:
    MoveEngine();
    ~MoveEngine();

    bool setPoint(QJsonObject JsonPoint);
    void execPoint();

private:
    Trajectory trajectory;
    AbstractPathGenerator *pathGenerator[2];
    AbstractPathGenerator *pathGene;


    void followTrajectory(const DataBasePositions *point);
    void requestCurrentPose(float *pointArr);
};

#endif