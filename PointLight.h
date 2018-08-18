#ifndef POINTLIGHT_H_INCLUDED
#define POINTLIGHT_H_INCLUDED

#include"Vector.h"
#include"Color.h"
class PointLight
{
private:
    Vec3 position;
    Color color;
public:
    PointLight()
    {
        position = Vec3(0,0,0);
        color = Color(1,1,1,0);
    }
    PointLight(Vec3 pos , Color c)
    {
        position = pos;
        color = c;
    }
    Vec3 getPosition() { return position; }
    Color getColor() { return color; }

    void setPosition(Vec3 pos) { position = pos ; }
    void setColor(Color c) { color = c ;}

};

#endif // POINTLIGHT_H_INCLUDED
