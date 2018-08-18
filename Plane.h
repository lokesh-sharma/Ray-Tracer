#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED
#include"Object.h"
#include"Vector.h"
#include"Ray.h"
#include"Color.h"

class Plane : public Object
{
private:
    Vec3 normal;
    double distanceFromOrigin;
    Color color;
public:
    Plane()
    {
        normal = Vec3(0,1,0);
        distanceFromOrigin = 0.0;
        color = Color(1,0,0,0);
    }
    Plane(Vec3 n , double distance , Color c)
    {
        normal = n.getNormalized();
        distanceFromOrigin = distance;
        color = c;
    }
    Vec3 getNormal() { return normal;}
    double getDistance() { return distanceFromOrigin;}
    Color getColor() { return color;}

    void setNormal(Vec3 n) { normal = n.getNormalized();}
    void setDistance(double d) { distanceFromOrigin = d;}
    void setColor(Color c) { color = c; }

    Vec3 getNormalAt(Vec3 point)
    {
        return normal;
    }

    double findIntersection(Ray ray)
    {
        Vec3 rayDir = ray.getRayDirection();
        double a = rayDir.dot(normal);
        if(a == 0)
        {
            return -1;
        }
        else
        {
            double b =normal.dot(ray.getRayOrigin().add(normal.scale(distanceFromOrigin).getNegative()));
            return -1*b/a;
        }
    }

};


#endif // PLANE_H_INCLUDED
