#ifndef _RENDER_TARGET_H
#define _RENDER_TARGET_H

#include <GL/glew.h>
#include "Texture.h"

class RenderTarget
{
    GLuint framebufferID;
    GLuint depthrenderbufferID;
    Texture texture;
    int height, width;
    int vw_bak;
    int vh_bak;
public:
    RenderTarget();
    RenderTarget(int width, int height);
    ~RenderTarget();

    void bind();
    void unbind();
    Texture getTexture();
    void remove();

};

#endif