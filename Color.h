#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

class Color{
private:
    double red;
    double green;
    double blue;
    double channel;
public:
    Color()
    {
        red = green = blue = channel = 0.0;
    }
    Color(double r , double g , double b , double ch)
    {
        red = r;
        green = g;
        blue = b;
        channel = ch;
    }
    double getRed() { return red;}
    double getGreen() { return green;}
    double getBlue() { return blue;}
    double getChannel() { return channel;}

    void setRed(double r ) { red = r;}
    void setGreen(double g ) { green = g;}
    void setBlue(double b ) { blue = b;}
    void setChannel(double ch ) { channel = ch;}

    Color scale(double f)
    {
        return Color(red*f , green*f , blue*f , channel);
    }
    Color add(Color c)
    {
        return Color(red + c.getRed() , green + c.getGreen() , blue + c.getBlue() , channel);
    }
    Color multiply(Color c)
    {
        return Color(red*c.getRed() , green*c.getGreen() , blue*c.getBlue() , channel);
    }
    Color average(Color c)
    {
        return Color((red + c.getRed())/2 , (green + c.getGreen())/2 , (blue + c.getBlue())/2 , channel);
    }
    Color clip()
    {

        if(red > 1)
            red = 1;
        if(green >1)
            green = 1;
        if(blue>1)
            blue = 1;

        return *this;


    }
};


#endif // COLOR_H_INCLUDED
