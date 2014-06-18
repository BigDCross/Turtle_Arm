#ifndef JOINT
#define JOINT

#include <Arduino.h>

class Joint
{
private:
    float length;
    int pos;
    int angle;

    void posToAngle ();
    void angleToPos ();

public:
    Joint ();
    Joint (float length_);
    Joint (float length_, int pos_);
    Joint (float length_, float angle_);

    void setLength (float length_);
    void setPos (int pos_);
    void setAngle (int angle_);

    float getLength ();
    int getPos ();
    float getAngle ();

} ;

#endif
