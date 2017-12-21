#include "Graphics.h"
Graphics::Graphics(Logic& logic) : logic(logic)
{
    glClearColor( 0.0,0.0,0.0, 1.0 );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND | GL_TEXTURE_2D );

    defaultShader = Shader::loadShaderFromFile("default");
    if( !defaultShader.isCompiled() )
    {
        printf("%s", defaultShader.getErrorString().c_str());
    }
    projectionMatrix = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);

    GLfloat vertices[] = {
        0.0, 0.0,
        640.0, 0.0,
        640.0, 480.0
    };
    vbo = -1;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    GLfloat texCoords[] = {
        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0
    };
    tbo = -1;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);

    testTexture = Texture("./resources/textures/lol.png");
}

void Graphics::render()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glUniformMatrix4fv(defaultShader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform1i(defaultShader.getUniformLocation("tex"), 0);

    defaultShader.bindArrayBuffer(defaultShader.getAttribLocation("vertexPos"), vbo, GL_FLOAT, 2, 2 * sizeof(GLfloat));
    defaultShader.bindArrayBuffer(defaultShader.getAttribLocation("textureCoords"), tbo, GL_FLOAT, 2, 2 * sizeof(GLfloat));
    defaultShader.bindTexture( GL_TEXTURE0, testTexture );

    defaultShader.use();

    glDrawArrays( GL_TRIANGLES, 0, 3 );
}