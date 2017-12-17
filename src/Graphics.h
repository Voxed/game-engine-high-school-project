#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logic.h"
#include "Shader.h"

class Graphics
{
    Logic& logic;

    glm::mat4 projectionMatrix;
    Shader defaultShader;
public:
    Graphics(Logic& logic);
    void render();
};
#endif