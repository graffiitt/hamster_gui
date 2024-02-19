
#include "PathGeneratorJoint.h"
#include "PathGeneratorLine.h"

enum TypePoint
{
    point,
    poseRegister
};

int main(int argc, char *argv[])
{
    QJsonObject _data;
    _data.insert("moveType", "linear");
    _data.insert("pointType", TypePoint::point);
    _data.insert("speed", 50);
    _data.insert("acc", 50);

    QJsonObject point;
    point.insert("coordType", CoordType::joint);
    point.insert("j1", 10);
    point.insert("j2", 20);
    point.insert("j3", 30);
    point.insert("j4", 40);
    _data.insert("point", point);

    // exec

    Trajectory trajectory;
    AbstractPathGenerator *pathGenerator[] = {new PathGeneratorJoint() };

    qDebug() << "set point " << trajectory.setTargetPoint(_data);

    // comppute trajectory
    AbstractPathGenerator *pathGene = pathGenerator[_data["point"].toObject()["coordType"].toInt()];
    pathGene->setTargetPoint(trajectory.getTargetPoint());
    pathGene->computeTrajectory(&trajectory);

    delete pathGenerator[0];
   // delete pathGenerator[1];
}