#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include<cmath>
#include<iostream>

class Vec3
{
private:
    double x;
    double y;
    double z;
public:
    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3(double X, double Y, double Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    double getX() { return x;}
    double getY() { return y;}
    double getZ() { return z;}

    double magnitute() { return std::sqrt(x*x + y*y + z*z) ;}
    void normalize()
    {
        double mag = magnitute();
        if( mag == 0)
        {
            std::cerr<<"Magnitute of vector cannot be Zero\n";
            return ;
        }
        x = x/mag;
        y = y/mag;
        z = z/mag;
    }
    Vec3 getNormalized()
    {
        double mag = magnitute();
        if( mag == 0)
        {
            std::cerr<<"Magnitute of vector cannot be Zero\n";
            return Vec3(0,0,0);
        }
        return Vec3(x/mag , y/mag ,z/mag);
    }
    Vec3 getNegative()
    {
        return Vec3(-x , -y , -z);
    }
    double dot(Vec3 op1)
    {
        return x*op1.getX() + y*op1.getY() + z*op1.getZ();
    }
    Vec3 cross(Vec3 op1)
    {
        double i = y*op1.getZ() - z*op1.getY();
        double j = z*op1.getX() - x*op1.getZ();
        double k = x*op1.getY() - y*op1.getX();
        return Vec3(i , j , k);

    }
    Vec3 add(Vec3 op1)
    {
        return Vec3(x + op1.getX() , y + op1.getY() , z + op1.getZ());
    }
    Vec3 subtract(Vec3 op1)
    {
        return Vec3(x - op1.getX() , y - op1.getY() , z - op1.getZ());
    }
    Vec3 scale(double op1)
    {
        return Vec3( x* op1 , y*op1 , z*op1);
    }
    Vec3 project(Vec3 b)
    {
        double factor = this->getNormalized().dot(b.getNormalized())*this->magnitute();
        return b.getNormalized().scale(factor);
    }
    Vec3 reflect(Vec3 normal)
    {
        return this->project(normal).scale(2.0).subtract(*this);
    }
    void showVector()
    {
        std::cout<<"( "<<x<<" , "<<y<<" , "<<z<<" )"<<std::endl;
    }

};


#endif // VECTOR_H_INCLUDED
