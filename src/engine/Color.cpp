#include "Color.h"

/**
 * @brief Initialize a new color object
 * 
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @param a Alpha value
 */
Color::Color(float r, float g, float b, float a) : Color(r,g,b)
{
    this->a = a;
}

/**
 * @brief Initialize a new color object
 * 
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 */
Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1.0;
}

/**
 * @brief Initialize an empty color object
 * 
 * ps. The default color object uses my favorite color! ^.^
 */
Color::Color() : r(0.0), g(1.0) , b(0.75), a(1.0)
{

} 