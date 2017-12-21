#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logic.h"
#include "Shader.h"
#include "Texture.h"

class Graphics
{
    Logic& logic;

    glm::mat4 projectionMatrix;
    GLuint vbo;
    GLuint tbo;
    Shader defaultShader;
    Texture testTexture;
public:
    Graphics(Logic& logic);
    void render();
};
#endif