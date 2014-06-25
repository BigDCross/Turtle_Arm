#ifndef VECTOR
#define VECTOR

/*
class fVector2
{
public:
    float x;
    float y;

    fVector2 (float x_, float y_)
    {
        x = x_;
        y = y_;
    }
} ;

class fVector3
{
public:
    float x;
    float y;
    float z;

    fVector3 (float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
} ;

class iVector2
{
public:
    int x;
    int y;

    iVector2 (int x_, int y_)
    {
        x = x_;
        y = y_;
    }
} ;

class iVector3
{
public:
    int x;
    int y;
    int z;

    iVector3 (int x_, int y_, int z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
} ;
*/

typedef struct fVector2
{
    float x;
    float y;
} fVector2 ;

typedef struct fVector3
{
    float x;
    float y;
    float z;
} fVector3 ;

typedef struct fVector5
{
    float f0;
    float f1;
    float f2;
    float f3;
    float f4;
} fVector5 ;

typedef struct iVector2
{
    int x;
    int y;
} iVector2 ;

typedef struct iVector3
{
    int x;
    int y;
    int z;
} iVector3 ;

#endif
