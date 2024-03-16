#include "MoveEngine.h"

MoveEngine::MoveEngine()
{
    maxAcc = 0.2;
    maxSpeed = 3.14;
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
    pathGene->setLimits(maxAcc / 100 * JsonPoint["acc"].toInt(), maxSpeed / 100 * JsonPoint["speed"].toInt());
    return trajectory.setTargetPoint(JsonPoint);
}

void MoveEngine::execPoint()
{
    // request current joint angle
    float currentPose[] = {1, 1, 1, 1};
    requestCurrentPose(currentPose);

    // set values
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
    for (int i = 0; i < point->joint2.size(); i++)

        qDebug() << "2: t: " << point->joint2.value(i)->time
                 << "sp:   " << point->joint2.value(i)->speed
                 << " dist:" << point->joint2.value(i)->angle;
}

void MoveEngine::requestCurrentPose(float *pointArr)
{
    pointArr[0] = 0;
    pointArr[1] = 0;
    pointArr[2] = 0;
    pointArr[3] = 0;
}
