#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

#include "Logic.h"
#include "Shader.h"
#include "Texture.h"

#include "SpriteBatch.h"
#include "Sprite.h"

class Graphics
{
    Logic& logic;

    glm::mat4 projectionMatrix;
    Shader defaultShader;
    Texture testTexture;
    Texture testTexture2;

    SpriteBatch batch;
public:
    Graphics(Logic& logic);
    void render();
};
#endif