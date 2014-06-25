#include <Joint.h>
#include <RobotArm.h>
#include <Vector.h>

RobotArm turtleArm;

void setup ()
{
    Serial.begin (9600);
    
    fVector3 target;  
    target.x = 0.0;
    target.y = 25.0;
    target.z = 0.0;

    Joint j1 (10.5, 512);
    Joint j2 (10.5, 512);
    Joint j3 (10.5, 512);

    turtleArm.addJoint (1, j1);
    turtleArm.addJoint (2, j2);
    turtleArm.addJoint (3, j3);
    turtleArm.calcFK ();

    Serial.print (turtleArm.currentArmPos.x);
    Serial.print (" ");
    Serial.print (turtleArm.currentArmPos.y);
    Serial.print (" ");
    Serial.println (turtleArm.currentArmPos.z);

    turtleArm.setTarget (target);
    turtleArm.calcIK ();

    Serial.print (turtleArm.currentArmPos.x);
    Serial.print (" ");
    Serial.print (turtleArm.currentArmPos.y);
    Serial.print (" ");
    Serial.println (turtleArm.currentArmPos.z);
    
    turtleArm.printJointPos ();
}

void loop ()
{
}
