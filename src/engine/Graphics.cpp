#include "Graphics.h"
/**
 * @brief Initialize new graphics object
 * 
 * @param core The main core
 * @param logic The logic object
 */
Graphics::Graphics(Core * core, Logic& logic) : logic(logic)
{
        
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );

    this->core = core;
}


/**
 * @brief The main rendering event
 * 
 * Called from the core
 * 
 */
void Graphics::render()
{
    Color c = core->getScreen()->backgroundColor;
    glClearColor( c.r, c.g, c.b, c.a );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    core->getScreen()->render(batch);

    batch.render(0, core->getWidth(), core->getHeight(), 0);
}