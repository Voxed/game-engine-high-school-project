#include "Color.h"

Color::Color(float r, float g, float b, float a) : Color(r,g,b)
{
    this->a = a;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color() : r(0.0), g(1.0) , b(0.75), a(1.0)
{

} 