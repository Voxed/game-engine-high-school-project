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
    /**
     * @brief Initialize an empty render target
     * 
     */
    RenderTarget();
    /**
     * @brief Initialize a render target
     * 
     * @param width Render target width
     * @param height Render target height
     */
    RenderTarget(int width, int height);
    //~RenderTarget();

    /**
     * @brief Bind the render target
     * 
     * All draw code will be directed at this target
     * 
     */
    void bind();
    /**
     * @brief Unbind the render target
     * 
     */
    void unbind();
    /**
     * @brief Get the render target texture
     * 
     * @return Texture The target texture
     */
    Texture getTexture();
    /**
     * @brief Clear the render target
     * 
     * Free up memory
     * 
     */
    void remove();
};

#endif