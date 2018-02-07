#include "RenderTarget.h"

/**
 * @brief Initialize an empty render target
 * 
 */
RenderTarget::RenderTarget() 
{
}

/**
 * @brief Initialize a render target
 * 
 * @param width Render target width
 * @param height Render target height
 */
RenderTarget::RenderTarget(int width, int height) 
{
    GLint dims[4] = {0};
    glGetIntegerv(GL_VIEWPORT, dims);
    vw_bak = dims[2];
    vh_bak = dims[3];

    this->height = height;
    this->width = width;
    glGenFramebuffers(1, &framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

    texture = Texture(width, height, GL_RGBA);

    glGenRenderbuffers(1, &depthrenderbufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbufferID);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTextureID(), 0);
    glClearColor(0,0,0,0);
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //TODO ERROR TESTING
}

/**
 * @brief Bind the render target
 * 
 * All draw code will be directed at this target
 * 
 */
void RenderTarget::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
    glViewport(0,0,width,height);
}

/**
 * @brief Unbind the render target
 * 
 */
void RenderTarget::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,vw_bak,vh_bak);
}

/**
 * @brief Get the render target texture
 * 
 * @return Texture The target texture
 */
Texture RenderTarget::getTexture()
{
    return texture;
}

/**
 * @brief Clear the render target
 * 
 * Free up memory
 * 
 */
void RenderTarget::remove()
{
    glDeleteFramebuffers(1, &framebufferID);
    glDeleteRenderbuffers(1, &depthrenderbufferID);
}