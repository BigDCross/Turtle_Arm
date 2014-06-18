#include <Arduino.h>

#include "RobotArm.h"
#include "Joint.h"
#include "Vector.h"

// Do most methods in this class even need to return anything?

RobotArm::RobotArm ()
{
    for (int i=0; i<NUMJOINTS; i++) { jointPositions[i] = 512; }

    // Vectors
    currentTarget.x = 0.0;
    currentTarget.y = 0.0;
    currentTarget.z = 0.0;

    currentPos.x = 0.0;
    currentPos.y = 0.0;
    currentPos.z = 0.0;

    finalPos.x = 0.0;
    finalPos.y = 0.0;
    finalPos.z = 0.0;

    jointOffset.x = 0.0;
    jointOffset.y = 0.0;
    jointOffset.z = 0.0;
}

void RobotArm::addJoint (int jointNum, Joint newJoint)
{
    joints[jointNum - 1] = newJoint;
}

void RobotArm::calcFK ()
{
    float cumAngle = 0;

    for (int i=0; i<NUMJOINTS; i++)
    {
        cumAngle += joints[i].getAngle ();

        calcOffset (joints[i].getLength(), cumAngle);

        currentPos.x += jointOffset.x;
        currentPos.y += jointOffset.y;
        currentPos.z += jointOffset.z;
    }
}

void RobotArm::calcIK ()
{

}

void RobotArm::calcGradient ()
{
    float dist = calcDistance (currentPos.x, currentPos.y, currentPos.z);

    while (dist > 0.1)
    {
        gradients.x = calcDistance (currentPos.x + 1, currentPos.y, currentPos.z) - calcDistance (currentPos.x - 1, currentPos.y, currentPos.z);
        gradients.y = calcDistance (currentPos.x, currentPos.y + 1, currentPos.z) - calcDistance (currentPos.x, currentPos.y - 1, currentPos.z);
        gradients.z = calcDistance (currentPos.x, currentPos.y, currentPos.z + 1) - calcDistance (currentPos.x, currentPos.y, currentPos.z - 1);
    }
}

void RobotArm::setTarget (fVector3 target)
{
    currentTarget = target;
}

float RobotArm::calcDistance (int x, int y, int z)
{
    float distance;

    distance +=  (x - currentTarget.x) * (x - currentTarget.x);
    distance +=  (y - currentTarget.y) * (y - currentTarget.y);
    distance +=  (z - currentTarget.z) * (z - currentTarget.z);

    return (sqrt (distance));
}

void RobotArm::calcOffset (float length, float cumAngle)
{
    // Might take radians
    jointOffset.x = length * sin (cumAngle);
    jointOffset.y = length * cos (cumAngle);
    jointOffset.z = 0;
}
