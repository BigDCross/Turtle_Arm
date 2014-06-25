#ifndef ROBOTARM
#define ROBOTARM

#include "Joint.h"
#include "Vector.h"

#define NUMJOINTS 3
#define TORADIANS (3.141592 / 180)
#define TODEGREES (180 / 3.141592)

class RobotArm
{
private:
    Joint joints[NUMJOINTS - 1];
    int jointPositions[NUMJOINTS - 1];
    fVector3 currentTarget;

    // Used in calculations
    fVector3 gradients;
    fVector3 finalPos;
    fVector3 jointOffset;

    float calcDistance (int x, int y, int z);
    inline void calcOffset (float length, float cumAngle);
    void calcGradient ();

public:
    fVector3 currentArmPos;
    fVector5 currentJointPos;

    RobotArm ();
    void addJoint (int jointNum, Joint newJoint);
    void setTarget (fVector3 target);
    void calcFK ();
    void calcIK ();
    void printJointPos ();
} ;

#endif
