#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logic.h"
#include "Shader.h"
#include "Texture.h"

#include "SpriteBatch.h"
#include "Sprite.h"

#include "Core.h"

class Core;
class Logic;
class Graphics
{
    Texture text;
    Shader shad;

    Logic& logic;

    glm::mat4 projectionMatrix;
    
    SpriteBatch batch;
    Core * core;
public:
    Graphics(Core * c, Logic& logic);
    void render();
};
#endif