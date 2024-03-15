#include "PathGeneratorJoint.h"

QList<Joint *> PathGeneratorJoint::getFirtsPath(float dq)
{
    QList<Joint *> points;
    float q = _limitSpeed * _limitSpeed / _limitAcc;
    if (q < abs(dq))
    {
        float ti = (abs(dq) - q) / _limitSpeed;
        float T = ti + 2 * _limitSpeed / _limitAcc;
        points.append(new Joint(0, 0));
        points.append(new Joint(_limitSpeed / _limitAcc, _limitSpeed));
        points.append(new Joint(_limitSpeed / _limitAcc + ti, _limitSpeed));
        points.append(new Joint(T, 0));
    }
    else if (q >= abs(dq))
    {
        float v11 = sqrt((2 * abs(dq)) / (2 / _limitAcc));
        float T = v11 / _limitAcc * 2;
        points.append(new Joint(0, 0));
        points.append(new Joint(v11 / _limitAcc, v11));
        points.append(new Joint(T, 0));
    }
    return points;
}

float PathGeneratorJoint::getTimeTravel(QList<Joint *> joint)
{
    return joint.value(joint.size() - 1)->time;
}

float PathGeneratorJoint::solveSpeed(float dq, float time)
{
    float d = time * time - 4 * 1 / _limitAcc * abs(dq);
    float x1 = (-time + sqrt(d)) / (-2 * 1 / _limitAcc);
    float x2 = (-time - sqrt(d)) / (-2 * 1 / _limitAcc);
    if (x1 < x2 && x1 > 0)
        return x1;
    return x2;
}

void PathGeneratorJoint::recomputePath(QList<Joint *> *joint, float timeTravel, float dq)
{
    /*
    var = trVel(deltaQ(4), t, a4, a4s);
    v4 = [0, double(var(1,1)), double(var(1,1)), 0];
    t4 = [0, double(var(1,1))/a4, t-double(var(1,1))/a4s, t];
    */
    // qDebug() << "speed joint recomp: " << solveSpeed(dq, timeTravel);

    float speed = solveSpeed(dq, timeTravel);

    int points = joint->size();
    if (points == 3)
    {
        delete joint->takeAt(2);
        delete joint->takeAt(1);
    }
    if (points == 4)
    {
        delete joint->takeAt(3);
        delete joint->takeAt(2);
        delete joint->takeAt(1);
    }
    joint->append(new Joint(speed / _limitAcc, speed));
    joint->append(new Joint(timeTravel - speed / _limitAcc, speed));
    joint->append(new Joint(timeTravel, 0));

    calcDistance(joint);
}

void PathGeneratorJoint::calcDistance(QList<Joint *> *joint)
{
    if (joint->size() == 3)
    {
        joint->value(0)->angle = 0;
        float dist_1 = _limitAcc * joint->value(1)->time * joint->value(1)->time / 2;
        joint->value(1)->angle = dist_1;

        float time_2 = joint->value(2)->time - joint->value(1)->time;
        float dist_2 = dist_1 + _limitAcc * time_2 * time_2 / 2;
        joint->value(2)->angle = dist_2;
    }
    else
    {
        joint->value(0)->angle = 0;
        float dist_1 = _limitAcc * joint->value(1)->time * joint->value(1)->time / 2;
        joint->value(1)->angle = dist_1;
        float dist_2 = dist_1 + (joint->value(2)->time - joint->value(1)->time) * joint->value(2)->speed;
        joint->value(2)->angle = dist_2;
        float time_3 = joint->value(3)->time - joint->value(2)->time;
        float dist_3 = dist_2 + _limitAcc * time_3 * time_3 / 2;
        joint->value(3)->angle = dist_3;
    }
}

void PathGeneratorJoint::setCurrentPoint(float *currentPoint)
{
    this->_currentPoint = currentPoint;
}

void PathGeneratorJoint::setTargetPoint(float *targetPoint)
{
    this->_targetPoint = targetPoint;
}

void PathGeneratorJoint::setLimits(float acceleration, float speedLimit)
{
    this->_limitAcc = acceleration;
    this->_limitSpeed = speedLimit;
}

void PathGeneratorJoint::computeTrajectory(Trajectory *trajectory)
{
    // convert point to joint if cartesian coords

    float deltaQ[] = {_targetPoint[0] - _currentPoint[0],
                      _targetPoint[1] - _currentPoint[1],
                      _targetPoint[2] - _currentPoint[2],
                      _targetPoint[3] - _currentPoint[3]};

    trajectory->dataPoints->joint1 = getFirtsPath(deltaQ[0]);
    trajectory->dataPoints->joint2 = getFirtsPath(deltaQ[1]);
    trajectory->dataPoints->joint3 = getFirtsPath(deltaQ[2]);
    trajectory->dataPoints->joint4 = getFirtsPath(deltaQ[3]);

    float maxTime = getTimeTravel(trajectory->dataPoints->joint1);
    if (maxTime < getTimeTravel(trajectory->dataPoints->joint2))
        maxTime = getTimeTravel(trajectory->dataPoints->joint2);
    if (maxTime < getTimeTravel(trajectory->dataPoints->joint3))
        maxTime = getTimeTravel(trajectory->dataPoints->joint3);
    if (maxTime < getTimeTravel(trajectory->dataPoints->joint4))
        maxTime = getTimeTravel(trajectory->dataPoints->joint4);

    recomputePath(&trajectory->dataPoints->joint1, maxTime, deltaQ[0]);
    recomputePath(&trajectory->dataPoints->joint2, maxTime, deltaQ[1]);
    recomputePath(&trajectory->dataPoints->joint3, maxTime, deltaQ[2]);
    recomputePath(&trajectory->dataPoints->joint4, maxTime, deltaQ[3]);
}
