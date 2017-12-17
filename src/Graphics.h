#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <GL/glew.h>

#include "Logic.h"

class Graphics
{
    Logic& logic;
public:
    Graphics(Logic& logic);
};
#endif