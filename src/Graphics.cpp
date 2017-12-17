#include "Graphics.h"
Graphics::Graphics(Logic& logic) : logic(logic)
{
    glClearColor( 0.91,0.91,0.94, 1.0 );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND | GL_TEXTURE_2D );

    
}

void Graphics::render()
{
    glClear( GL_COLOR_BUFFER_BIT );
}