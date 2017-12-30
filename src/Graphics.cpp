#include "Graphics.h"
Graphics::Graphics(Logic& logic) : logic(logic)
{
    glClearColor( 0.0,1.0,0.5, 1.0 );
    glEnable( GL_DEPTH_TEST );

    defaultShader = Shader::loadShaderFromFile("default");
    if( !defaultShader.isCompiled() )
    {
        printf("%s", defaultShader.getErrorString().c_str());
    }
    projectionMatrix = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);

    testTexture = Texture("./resources/textures/lol.png");

    batch.draw(Sprite(&testTexture, &defaultShader, 12, 10, 0.0f, 1.0f, 1.0f));
    batch.draw(Sprite(&testTexture, &defaultShader, 13, 10, 0.0f, 1.0f, 1.0f));
    batch.draw(Sprite(&testTexture, &defaultShader, 10, 10, 0.0f, 1.0f, 1.0f));
    batch.draw(Sprite(&testTexture, &defaultShader, 20, -15, -0.5f, 10.0f, 10.0f));
}



void Graphics::render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;

    struct DrawRange
    {
        int elements;
        Texture* texture;
        Shader* shader;
    };
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> orderedSpriteList = batch.getOrdererdSprites();
    std::vector<DrawRange> ranges;
    Shader* last_shader = 0;
    Texture* last_texture = 0;


    for(auto &e: orderedSpriteList) //Loop through all shader changes
    {
        Shader* curr_shader = e.first;
        for(auto &e2: e.second) //Loop through all texture changes for shader change
        {
            Texture* curr_texture = e2.first; 

            DrawRange dr = DrawRange(); //Create a clean drawrange
            dr.texture = 0; //Set texturechange to null, meaning the range doesnt need a new texture
            dr.shader = 0; //Set shaderchange to null, meaning the range doesnt need a new shader
            if(e.first != last_shader) //Wait, does it need a shaderchange?
            {
                dr.shader = e.first; //Oh shit! It does.
            }
            if(e2.first != last_texture) //Do we need a texture change though?
            {
                dr.texture = e2.first; //Gosh darn! We do!
            }
            std::vector<Sprite*> sprites = e2.second; //Which sprites are to be part of this range?
            for(auto &sprite: sprites)
            {
                dr.elements += 1;
                //Apply sprites to indices/vertices/texcoords
                uint vertices_offset = vertices.size()/3;
                int x = sprite->x;
                int y = sprite->y;
                float z = sprite->z;
                float scaleX = sprite->scaleX;
                float scaleY = sprite->scaleY;
                int texWidth = sprite->getTexture()->getWidth();
                int texHeight = sprite->getTexture()->getHeight();
                for(uint i = 0; i < sizeof(Sprite::VERTICES)/sizeof(Sprite::VERTICES[0]); i+=2)
                {
                    float vertX = Sprite::VERTICES[i];
                    float vertY = Sprite::VERTICES[i+1];
                    vertices.push_back(vertX*texWidth*scaleX+x);
                    vertices.push_back(vertY*texHeight*scaleY+y);
                    vertices.push_back(z);
                }
                for(uint i = 0; i < sizeof(Sprite::TEX_COORDS)/sizeof(Sprite::TEX_COORDS[0]); i+=2)
                {
                    float coordX = Sprite::TEX_COORDS[i];
                    float coordY = Sprite::TEX_COORDS[i+1];
                    texCoords.push_back(coordX);
                    texCoords.push_back(coordY);
                }
                for(uint i = 0; i < sizeof(Sprite::INDICES)/sizeof(Sprite::INDICES[0]); i+=2)
                {
                    uint indexX = Sprite::INDICES[i];
                    uint indexY = Sprite::INDICES[i+1];
                    indices.push_back(vertices_offset + indexX);
                    indices.push_back(vertices_offset + indexY);
                }


            }
            ranges.push_back(dr); //Drawrange complete!

            //printf("Range completed, length: %u with directives:\n", dr.elements);
            //if(dr.texture != 0) printf("change texture\n");
            //if(dr.shader != 0) printf("change shader\n");

            last_texture = e2.first;
            last_shader = e.first;
        }
    }


    GLuint vbo = -1;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    GLuint tbo = -1;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), &texCoords[0], GL_STATIC_DRAW);

    GLuint ibo = -1;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    //Fake test lol
    glUniformMatrix4fv(defaultShader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform1i(defaultShader.getUniformLocation("tex"), 0);

    defaultShader.bindArrayBuffer(defaultShader.getAttribLocation("vertexPos"), vbo, GL_FLOAT, 3, 3 * sizeof(GLfloat));
    defaultShader.bindArrayBuffer(defaultShader.getAttribLocation("textureCoords"), tbo, GL_FLOAT, 2, 2 * sizeof(GLfloat));
    defaultShader.bindTexture( GL_TEXTURE0, testTexture );

    defaultShader.use();

    glDrawElements( GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}