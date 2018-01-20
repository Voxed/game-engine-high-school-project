#include "Graphics.h"
Graphics::Graphics(Core * core, Logic& logic) : logic(logic)
{
    Color c = core->getScreen()->getBackgroundColor();
    glClearColor( c.r, c.g, c.b, c.a );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );

    projectionMatrix = glm::ortho(0.0f, (float)core->getWidth(), (float)core->getHeight(), 0.0f, 1.0f, -1.0f);

    this->core = core;
}



void Graphics::render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    core->getScreen()->render(batch);

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;

    struct DrawRange
    {
        int elements = 0;
        Texture* texture = 0;
        Shader* shader = 0;
        bool transparent = false;
    };
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> opaqueSprites = batch.getOpaqueSprites();
    std::vector<DrawRange> ranges;
    Shader* last_shader = 0;
    Texture* last_texture = 0;


    //Generate draw data :)
    for(auto &e: opaqueSprites) //Loop through all shader changes
    {
        Shader* curr_shader = e.first;
        for(auto &e2: e.second) //Loop through all texture changes for shader change
        {
            Texture* curr_texture = e2.first; 

            DrawRange dr = DrawRange(); //Create a clean drawrange
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

                std::vector<GLfloat> vert;
                std::vector<GLuint> ind;
                std::vector<GLfloat> tc;

                sprite->getData(vert,tc,ind, vertices_offset);
                vertices.insert(vertices.end(), vert.begin(), vert.end());      
                indices.insert(indices.end(), ind.begin(), ind.end());             
                texCoords.insert(texCoords.end(), tc.begin(), tc.end());  
            }
            ranges.push_back(dr);

            last_texture = e2.first;
            last_shader = e.first;
            
        }
    }




    std::vector<Sprite*> transparentSprites = batch.getTransparentSprites();

    //Generate transparent draw data, these sprites are less effective but required for showing partial transparency.
    for(auto &sprite: transparentSprites)
    {
        DrawRange dr;
        dr.elements = 1;
        dr.texture = sprite->getTexture();
        dr.transparent = true;
        dr.shader = sprite->getShader();
        //Apply sprites to indices/vertices/texcoords
        uint vertices_offset = vertices.size()/3;

        std::vector<GLfloat> vert;
        std::vector<GLuint> ind;
        std::vector<GLfloat> tc;

        sprite->getData(vert,tc,ind, vertices_offset);
        vertices.insert(vertices.end(), vert.begin(), vert.end());      
        indices.insert(indices.end(), ind.begin(), ind.end());             
        texCoords.insert(texCoords.end(), tc.begin(), tc.end());    
        ranges.push_back(dr);
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

    uint offset = 0;
    for(auto &range: ranges)
    {
        if(range.transparent) 
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        if(range.texture)
        {
            range.texture->bind(GL_TEXTURE0);
        }
        if(range.shader)
        {
            glUniformMatrix4fv(range.shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniform1i(range.shader->getUniformLocation("tex"), 0);

            range.shader->bindArrayBuffer(range.shader->getAttribLocation("vertexPos"), vbo, GL_FLOAT, 3, 3 * sizeof(GLfloat));
            range.shader->bindArrayBuffer(range.shader->getAttribLocation("textureCoords"), tbo, GL_FLOAT, 2, 2 * sizeof(GLfloat));
            
            range.shader->use();

        }
        

        glDrawElements( GL_TRIANGLES, 6 * range.elements, GL_UNSIGNED_INT, (void*) (offset*sizeof(GLuint)));
        offset += 6 * range.elements;

        if(range.transparent)
        {
            glDisable(GL_BLEND);
        }
    }

    batch.clear();
}