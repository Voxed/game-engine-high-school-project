#include "Graphics.h"
Graphics::Graphics(Logic& logic) : logic(logic)
{
    glClearColor( 0.91,0.91,0.94, 1.0 );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND | GL_TEXTURE_2D );

    defaultShader = Shader::loadShaderFromFile("./default");
    if( !defaultShader.isCompiled() )
    {
        printf("%s", defaultShader.getErrorString().c_str());
    }
    projectionMatrix = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f);
    
}

void Graphics::render()
{
    glUseProgram(defaultShader.getProgramID());
    glUniform4fv(defaultShader.getUniformLocation("projectionMatrix"), 1, glm::value_ptr(projectionMatrix));
    glClear( GL_COLOR_BUFFER_BIT );

    
}