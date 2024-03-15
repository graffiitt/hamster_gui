#ifndef KINEMATICSSOLVER_H
#define KINEMATICSSOLVER_H

 

class KinematicsSolver
{
public:
    bool checkCoordCart(const float *arrPoints);
    bool checkCoordJoint(const float *arrPoints);
    void forward();
    void inverse();
};

#endif