#include <iostream>
#include <fstream>
#include<sstream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include"Vector.h"
#include"Ray.h"
#include"Camera.h"
#include"Color.h"
#include"PointLight.h"
#include"Sphere.h"
#include"Plane.h"

const int width = 640;
const int height = 480;
const double aspectRatio = double(width)/double(height);
const double ambientLight = 0.2;
const double diffuseFactor = 2.0;
const int specularFactor = 10.0;
const double specularIntensity = 2.0;
const double accuracy = 0.000001;

struct RGBType{
    double r ;
    double g ;
    double b ;
};

void savebmp(const char* fileName , int w , int h , int dpi , RGBType* data)
{
    FILE* f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s ;
    double factor = 39.375 ;
    int m = (int)(factor);
    int ppm = dpi*m;
    unsigned char bmpfileheader[14] = {'B' , 'M' , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 54 , 0 , 0 , 0 };
    unsigned char bmpinfoheader[40] = { 40 , 0 , 0 ,0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,0 ,1,24,0};

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w>>8);
    bmpinfoheader[6] = (unsigned char)(w>>16);
    bmpinfoheader[7] = (unsigned char)(w>>24);


    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm>>8);
    bmpinfoheader[27] = (unsigned char)(ppm>>16);
    bmpinfoheader[28] = (unsigned char)(ppm>>24);

    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm>>8);
    bmpinfoheader[31] = (unsigned char)(ppm>>16);
    bmpinfoheader[32] = (unsigned char)(ppm>>24);

    f = fopen(fileName , "wb");
    fwrite(bmpfileheader ,1, 14 , f);
    fwrite(bmpinfoheader , 1 , 40 , f);

    for( int  i = 0 ; i < k ; i++)
    {
        RGBType rgb = data[i];
        int  r =  data[i].r*255;
        int g =  data[i].g*255;
        int b =  data[i].b*255;

        unsigned char color[3] = { b , g , r};

        fwrite(color , 1 , 3 , f);
    }
    fclose(f);

}
int getclosestObjectIndex(std::vector<double> intersections)
{
    if(intersections.size() == 0)
        return -1;
    else if( intersections.size() == 1)
    {
        if(intersections.at(0) > 0)
            return 0;
        else
            return -1;
    }
    int index = -1;
    double value = intersections.at(0);
    if(value > 0)
        index = 0;
    for( int i = 1 ; i<intersections.size() ; i++)
    {
        if( value < 0 && intersections.at(i) > 0)
        {
            value = intersections.at(i);
            index = i;
        }

        if(intersections.at(i) < value && value > 0 && intersections.at(i) >0)
        {
            value = intersections.at(i);
            index = i;
        }
    }
    return index;

}
Color getPixelColor(std::vector<Object*> sceneObjects , std::vector<PointLight*>sceneLights,
                    int objectIndex , Vec3 pointOfIntersection , Vec3 camPos)
{
    Color ambient(ambientLight , ambientLight , ambientLight , 0);
    Object* object = sceneObjects.at(objectIndex);
    Color objectColor = sceneObjects.at(objectIndex)->getColor();
    Vec3 normalAtIntersection = sceneObjects.at(objectIndex)->getNormalAt(pointOfIntersection);
    Color finalColor(0,0,0,0);
    double factor;
    for(int i = 0 ; i< sceneLights.size() ; i++)
    {
        Vec3 rayOrigin = pointOfIntersection;
        Vec3 rayDirection = sceneLights.at(i)->getPosition().subtract(pointOfIntersection).getNormalized();
        Ray shadowRay(rayOrigin , rayDirection);

        Vec3 distanceToLight = sceneLights.at(i)->getPosition().subtract(rayOrigin);
        Vec3 distanceToLightVector = distanceToLight.getNormalized();
        factor = distanceToLightVector.dot(normalAtIntersection.getNormalized());
        bool inShadow = false;
        Color color;
        if(factor > 0)
        {
            color = sceneLights.at(i)->getColor().scale(factor).multiply(objectColor);
            Vec3 toEyeVector = camPos.subtract(pointOfIntersection).getNormalized();
            Vec3 reflected = distanceToLightVector.project(normalAtIntersection);
            double specFactor = toEyeVector.dot(reflected);
            if(specFactor > 0){
                Color specColor = Color(1,1,1,0);
                color = color.add(specColor.scale( std::pow(specFactor, specularFactor)*specularIntensity));
            }

        }
        else
            inShadow = true;
        if(factor >0)
        {
            for(int index = 0 ; index < sceneObjects.size() ; index++)
            {
                double intersect = sceneObjects.at(index)->findIntersection(shadowRay);
                if(intersect > 0.01 && intersect < distanceToLight.magnitute())
                {
                    inShadow = true;
                    break;
                }
            }
        }
        if(inShadow == false)
            finalColor = finalColor.add(color);
    }

    finalColor =  finalColor.add(ambient.multiply(objectColor));
    return finalColor.scale(1.0).clip();
}
int main()
{

    int dpi = 72;

    RGBType* pixels = new RGBType[width*height];

    Vec3 X(1,0,0);
    Vec3 Y(0,1,0);
    Vec3 Z(0,0,1);
    Vec3 camPos(0,2,5);

    Vec3 lookAt(0, 0, 0);
    Vec3 diffBtw(camPos.getX() - lookAt.getX() , camPos.getY() - lookAt.getY() , camPos.getZ() - lookAt.getZ());
    Vec3 camdir = diffBtw.getNegative().getNormalized();
    Vec3 camright = camdir.cross(Y).getNormalized();
    Vec3 camdown = camdir.cross(camright).getNormalized();
    Camera camera(camPos , camdir , camright , camdown);

    Vec3 lightpos (-3 , 3 , 3);
    Color lightcolor ( 1 , 1, 1, 0);
    PointLight light =  PointLight(lightpos , lightcolor);

    Color c1(0.5 , 0.7 , 0.1 , 0);
    Color c2(0.5 , 0.5, 0.5 , 0);
    Color c3(0.5 , 0.5, 0.8 , 0);

    Plane scenePlane(Y , -1 ,c2);
    Sphere sceneSphere(1.0 , Vec3(0,0,0) , c1);
    Sphere sceneSphere2(0.5 , Vec3(1.3,-0.5,1) , c3);

    std::vector<Object*> sceneObjects;
    sceneObjects.push_back(&scenePlane);
    sceneObjects.push_back(&sceneSphere);
    sceneObjects.push_back(&sceneSphere2);

    std::vector<PointLight*>sceneLights;
    sceneLights.push_back(&light);

    double xamnt , yamnt;

    std::cout << "Rendering.." <<std::endl;
    for( int x = 0 ; x < width ; x++)
    {
        for( int  y = 0 ; y < height ; y++)
        {
            if(width > height)
            {
                xamnt = ((x+0.5)/width)*aspectRatio - ((width-height)/double(height))/2;
                yamnt = ((height-y)+0.5)/height;
            }
            else if(height > width)
            {
                xamnt = (x+0.5)/width;
                yamnt = (((height-y)+0.5)/height)/aspectRatio - (((height-width)/double(width))/2);

            }
            else
            {
                xamnt = (x+ 0.5)/width;
                yamnt = ((height-y)+0.5)/height;
            }
            Vec3 camRayOrigin = camera.getCamPos();
            Vec3 camRayDir = camera.getCamDir().add(camright.scale(xamnt-0.5).add(camdown.scale(yamnt - 0.5))).getNormalized();
            Ray camRay(camRayOrigin , camRayDir);

            std::vector<double> intersections;

            for(int index = 0 ; index < sceneObjects.size() ; index++)
            {
                double intersect = sceneObjects.at(index)->findIntersection(camRay);
                intersections.push_back(intersect);
            }
            int closestObject = getclosestObjectIndex(intersections);
            Color objColor;
            if(closestObject>=0)
            {
                Vec3 pointOfIntersection = camRayOrigin.add(camRayDir.scale(intersections.at(closestObject)));
                objColor = getPixelColor(sceneObjects , sceneLights , closestObject , pointOfIntersection , camPos);
            }


            int current = y*width + x;
            pixels[current].r = objColor.getRed();
            pixels[current].g = objColor.getGreen();
            pixels[current].b = objColor.getBlue();

        }
    }
    std::cout << "Done!!" << std::endl;
    savebmp("scene.bmp" , width , height , dpi , pixels);
    return 0;
}
