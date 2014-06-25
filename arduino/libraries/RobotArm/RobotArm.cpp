#include <Arduino.h>

#include "RobotArm.h"
#include "Joint.h"
#include "Vector.h"

// Do most methods in this class even need to return anything? Answer: No

// Arm Control Procedure:
// Define default position of arm. (And probably move there.)
// Perform FK for default pos.
// Pass in desired position. (check constraints, blah blah blah)
// Find distance from desired position.
// Perform gradient search. Recalculate FK each iteration. (Keep iterations low) [Maybe set accuracy modes?]
// Finish moving (and reset target?)

RobotArm::RobotArm ()
{
    for (int i=0; i<NUMJOINTS; i++) { jointPositions[i] = 512; }

    // Vectors
    currentTarget.x = 0.0;
    currentTarget.y = 0.0;
    currentTarget.z = 0.0;

    currentArmPos.x = 0.0;
    currentArmPos.y = 0.0;
    currentArmPos.z = 0.0;

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
    float cumAngle = 0.0;

    for (int i=0; i<NUMJOINTS; i++)
    {
        cumAngle += joints[i].getAngle ();

        calcOffset (joints[i].getLength(), cumAngle);

        currentArmPos.x += jointOffset.x;
        currentArmPos.y += jointOffset.y;
        currentArmPos.z += jointOffset.z;

        Serial.print (jointOffset.x);
        Serial.print (jointOffset.y);
        Serial.print (jointOffset.z);
        Serial.println ();
    }
}

void RobotArm::calcIK ()
{
    calcGradient ();
}

void RobotArm::calcGradient ()
{
    // XXX: REDO! Works with servo positions not currentArmPos
    float dist = calcDistance (currentArmPos.x, currentArmPos.y, currentArmPos.z);

    while (dist > 0.1)
    {
        gradients.x = calcDistance (joints[0].pos + 1, joints[1].pos, joints[2].pos) - (joints[0].pos - 1, joints[1].pos, joints[2].pos);
        gradients.y = calcDistance (joints[0].pos, joints[1].pos + 1, joints[2].pos) - (joints[0].pos, joints[1].pos - 1, joints[2].pos);
        gradients.z = calcDistance (joints[0].pos, joints[1].pos, joints[2].pos + 1) - (joints[0].pos, joints[1].pos, joints[2].pos - 1);

        joints[0].pos -= gradients.x;
        joints[1].pos -= gradients.y;
        joints[2].pos -= gradients.z;

        //Serial.print ((int)joints[0].pos);
        //Serial.print (" ");
        //Serial.print ((int)joints[1].pos);
        //Serial.print (" ");
        //Serial.println ((int)joints[2].pos);
        
        //Serial.print (currentArmPos.x);
        //Serial.print (" ");
        //Serial.print (currentArmPos.y);
        //Serial.print (" ");
        //Serial.println (currentArmPos.z);
        
        calcFK ();

        dist = calcDistance (currentArmPos.x, currentArmPos.y, currentArmPos.z);

        //Serial.println (dist);
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

inline void RobotArm::calcOffset (float length, float cumAngle)
{
    jointOffset.x = length * sin (cumAngle * TORADIANS);
    jointOffset.y = length * cos (cumAngle * TORADIANS);
    jointOffset.z = 0.0;
}

void RobotArm::printJointPos ()
{
    Serial.println ("Joint Positions:");

    for (int i=0; i<NUMJOINTS; i++)
    {
        Serial.print (joints[i].getPos ());
        Serial.print (" ");
    }

    Serial.println ();
}
