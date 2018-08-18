#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include"Vector.h"
#include"Color.h"
#include"Ray.h"

class Object
{
private:
public:
    Object(){}
    virtual Color getColor()=0 ;
    virtual Vec3 getNormalAt(Vec3 point) {}
    virtual double findIntersection(Ray ray) { return 0;}
};


#endif // OBJECT_H_INCLUDED
