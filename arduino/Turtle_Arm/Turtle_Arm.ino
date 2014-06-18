#include <Joint.h>
#include <RobotArm.h>
#include <Vector.h>

RobotArm turtleArm;

void setup ()
{
    Serial.begin (9600);

    Joint j1 (10.5, 512);
    Joint j2 (10.5, 512);
    Joint j3 (10.5, 512);

    turtleArm.addJoint (1, j1);
    turtleArm.addJoint (2, j2);
    turtleArm.addJoint (3, j3);
    turtleArm.calcFK ();

    Serial.print (turtleArm.currentPos.x);
    Serial.print (" ");
    Serial.print (turtleArm.currentPos.y);
    Serial.print (" ");
    Serial.println (turtleArm.currentPos.z);

}

void loop ()
{
}
