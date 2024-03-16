#include "MoveEngine.h"

MoveEngine::MoveEngine()
{
    pathGenerator[0] = new PathGeneratorJoint();
    // pathGenerator[1] = new PathGeneratorLine();
}

MoveEngine::~MoveEngine()
{
    delete pathGenerator[0];
    delete pathGenerator[1];
}

bool MoveEngine::setPoint(QJsonObject JsonPoint)
{
    if (JsonPoint["moveType"].toInt() > 1)
        return false;
    pathGene = pathGenerator[JsonPoint["moveType"].toInt()];
    return trajectory.setTargetPoint(JsonPoint);
}

void MoveEngine::execPoint()
{
    // request current joint angle
    float currentPose[] = {1, 1, 1, 1};
    requestCurrentPose(currentPose);

    // set values
    pathGene->setLimits(0.1, 1);
    pathGene->setCurrentPoint(currentPose);
    pathGene->setTargetPoint(trajectory.getTargetPoint());

    // compute trajectory
    pathGene->computeTrajectory(&trajectory);

    // follow trjectory
    // points contained in trajectory->dataPoints->joint*
    this->followTrajectory(trajectory.dataPoints);
    trajectory.clearMemoryPoints();
}

void MoveEngine::followTrajectory(const DataBasePositions *point)
{



 
    for (int i = 0; i < point->joint1.size(); i++)
        qDebug() << "1: t: " << point->joint1.value(i)->time
                 << "sp: " << point->joint1.value(i)->speed
                 << " dist:" << point->joint1.value(i)->angle;
}

void MoveEngine::requestCurrentPose(float *pointArr)
{
    pointArr[0] = 0;
    pointArr[1] = 0;
    pointArr[2] = 0;
    pointArr[3] = 0;
}
