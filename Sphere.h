#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include"Vector.h"
#include"Color.h"
#include"Object.h"

class Sphere : public Object
{
private:
    double radius ;
    Vec3 position;
    Color color;

public:
    Sphere()
    {
        radius = 1;
        position = Vec3(0,0,0);
        color = Color(1,0,0,0);
    }
    Sphere(double r , Vec3 pos , Color c)
    {
        radius = r;
        position = pos;
        color = c;
    }

    double getRadius(){ return radius ;}
    Vec3 getPosition() { return position ;}
    Color getColor() { return color;}

    void setRadius(double r) { radius = r ;}
    void setPosition(Vec3 pos) { position = pos; }
    void setColor(Color c) { color = c; }

    Vec3 getNormalAt(Vec3 point)
    {
        Vec3 nrm = Vec3(point.getX() - position.getX() , point.getY() - position.getY() , point.getZ()-position.getZ());
        return nrm.getNormalized();
    }
    double findIntersection(Ray ray)
    {
        Vec3 rayOrigin = ray.getRayOrigin();
        double rayOriginX = rayOrigin.getX();
        double rayOriginY = rayOrigin.getY();
        double rayOriginZ = rayOrigin.getZ();

        Vec3 rayDirection = ray.getRayDirection();
        double rayDirX = rayDirection.getX();
        double rayDirY = rayDirection.getY();
        double rayDirZ = rayDirection.getZ();

        Vec3 sphereCenter = position;
        double centerX = sphereCenter.getX();
        double centerY = sphereCenter.getY();
        double centerZ = sphereCenter.getZ();

        double a = 1;
        double b = 2*(rayOriginX - centerX)*rayDirX +
                2*(rayOriginY - centerY)*rayDirY +
                2*(rayOriginZ - centerZ)*rayDirZ ;

        double c = std::pow(rayOriginX - centerX , 2) +
                std::pow(rayOriginY - centerY , 2)+
                std::pow(rayOriginZ - centerZ , 2) -
                radius*radius;

        double D = b*b - 4*a*c;

        if(D > 0)
        {
            double root1 = (-b - sqrt(D))/2;
            double root2 = (-b + sqrt(D))/2;
            if(root1 > 0)
                return root1;
            else
                return root2;
        }
        else
            return -1;
    }
};


#endif // SPHERE_H_INCLUDED
