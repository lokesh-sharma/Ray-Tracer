#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include"Vector.h"

class Camera
{
private:
    Vec3 camPosition;
    Vec3 camDirection;
    Vec3 camRight;
    Vec3 camDown;
public:

    Camera()
    {
        camPosition = Vec3(0,0,0);
        camDirection = Vec3(0,0,1);
        camRight = Vec3(0,0,0);
        camDown = Vec3(0,0,0);
    }
    Camera(Vec3 pos , Vec3 dir , Vec3 right , Vec3 down)
    {

        camPosition = pos;
        camDirection = dir;
        camRight = right;
        camDown = down;
    }

    Vec3 getCamPos() { return camPosition ; }
    Vec3 getCamDir() { return camDirection ; }
    Vec3 getCamRight() { return camRight; }
    Vec3 getCamDown() { return camDown; }
};


#endif // CAMERA_H_INCLUDED
