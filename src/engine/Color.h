#ifndef _COLOR_H
#define _COLOR_H

class Color
{
public:
    /**
     * @brief Initialize a new color object
     * 
     * @param r Red value
     * @param g Green value
     * @param b Blue value
     * @param a Alpha value
     */
    Color(float r, float g, float b, float a);
    /**
     * @brief Initialize a new color object
     * 
     * @param r Red value
     * @param g Green value
     * @param b Blue value
     */
    Color(float r, float g, float b);
    /**
     * @brief Initialize an empty color object
     * 
     * ps. The default color object uses my favorite color! ^.^
     */
    Color();
    float r, g, b ,a;
};

#endif