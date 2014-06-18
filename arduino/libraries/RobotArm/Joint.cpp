#include <Arduino.h>

#include "Joint.h"

Joint::Joint ()
{
    length = 0;
    pos = 0;
    angle = 0;
}

Joint::Joint (float length_)
{
   length = length_; 
}

Joint::Joint (float length_, int pos_)
{
   length = length_; 
   pos = pos_;
   posToAngle ();
}

Joint::Joint (float length_, float angle_)
{
   length = length_; 
   angle = angle_;
   angleToPos (); 
}

void Joint::posToAngle ()
{
    // Add 30 to account for servo range
    // Subtract 180 to adjust frame of reference
    angle = (pos * 0.29) + 30 - 180;
}

void Joint::angleToPos ()
{
    pos = (angle - 30) / 0.29;
}

void Joint::setLength (float length_)
{
    length = length_;
}

void Joint::setPos (int pos_)
{
    pos = pos_;
    posToAngle ();
}

void Joint::setAngle (int angle_)
{
    angle = angle_;
    angleToPos ();
}

float Joint::getLength ()
{
    return length;
}

int Joint::getPos ()
{
    return pos;
}

float Joint::getAngle ()
{
    return angle;
}
