#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include<cmath>
#include"Vector.h"
class Ray
{
private:
    Vec3 origin;
    Vec3 direction;
public:
    Ray()
    {
        origin = Vec3();
        direction = Vec3(1,0,0);
    }
    Ray(Vec3 orgn , Vec3 dir)
    {
        origin = orgn ;
        direction = dir;
    }
    Vec3 getRayOrigin() { return origin;}
    Vec3 getRayDirection() { return direction;}

};

#endif // RAY_H_INCLUDED
