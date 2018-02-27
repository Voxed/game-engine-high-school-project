#include "Graphics.h"

Graphics::Graphics(Core * core, Logic& logic) : logic(logic)
{
        
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );

    this->core = core;

    batch = SpriteBatch(core->getHeight(), core->getWidth());
}

void Graphics::render()
{
    Color c = core->getScreen()->backgroundColor;
    glClearColor( c.r, c.g, c.b, c.a );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    core->getScreen()->render(batch);

    batch.render(0, core->getWidth(), core->getHeight(), 0);
}