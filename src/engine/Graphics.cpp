#include "Graphics.h"
Graphics::Graphics(Core * core, Logic& logic) : logic(logic)
{
    
    Color c = core->getScreen()->getBackgroundColor();
    glClearColor( c.r, c.g, c.b, c.a );
    
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );

    this->core = core;
}



void Graphics::render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    core->getScreen()->render(batch);

    batch.render(0, core->getWidth(), core->getHeight(), 0);
}