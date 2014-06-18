#ifndef ROBOTARM
#define ROBOTARM

#include <Arduino.h>

#include "Joint.h"
#include "Vector.h"

#define NUMJOINTS 3

class RobotArm
{
private:
    Joint joints[NUMJOINTS];
    int jointPositions[NUMJOINTS];
    fVector3 currentTarget;

    // Used in calculations
    fVector3 gradients;
    fVector3 finalPos;
    fVector3 jointOffset;

    float calcDistance (int x, int y, int z);
    void calcOffset (float length, float cumAngle);

public:
    fVector3 currentPos;

    RobotArm ();
    void addJoint (int jointNum, Joint newJoint);
    void setTarget (fVector3 target);
    void calcFK ();
    void calcIK ();
    void calcGradient ();
} ;

#endif
