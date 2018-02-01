#include "SpriteBatch.h"

void SpriteBatch::draw(Sprite sprite)
{
    sprites.push_back(sprite);
}

void SpriteBatch::draw(std::vector<Sprite> sprites)
{
    for(auto sprite : sprites)
    {
        draw(sprite);
    }
}

std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> SpriteBatch::getOpaqueSprites()
{

    //constructing
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> sprites_by_texture_by_shader;
    for(auto &sprite: sprites)
    {
        if( !sprite.usePartialTransparency )
        {
            if( !sprites_by_texture_by_shader.count( sprite.getShader() ) )
            {
                sprites_by_texture_by_shader.insert(std::make_pair(sprite.getShader(), std::map<Texture*, std::vector<Sprite*>>()));
            }

            if( !sprites_by_texture_by_shader.at(sprite.getShader()).count( sprite.getTexture() ) )
            {
                sprites_by_texture_by_shader.at(sprite.getShader()).insert(std::make_pair( sprite.getTexture(), std::vector<Sprite*>()));
            }
            sprites_by_texture_by_shader.at(sprite.getShader()).at(sprite.getTexture()).push_back(&sprite);
        }
    }

    return sprites_by_texture_by_shader;
};

std::vector<Sprite*> SpriteBatch::getTransparentSprites()
{
    std::vector<Sprite*> sorted_sprites;
    for(auto &sprite: sprites)
    {
        if( sprite.usePartialTransparency )
        {
            sorted_sprites.push_back(&sprite);
        }
    }
    std::sort(sorted_sprites.begin(), sorted_sprites.end(), []( Sprite*& lhs, Sprite*& rhs){ return lhs->z < rhs->z; });
    return sorted_sprites;
}

void SpriteBatch::clear()
{
    //Remove all temporary textures
    for(auto &s : sprites)
    {
        if(s.useTempTexture)
        {
            GLuint id = s.getTexture()->getTextureID();
            glDeleteTextures(1, &id);
        }
    }
    sprites.clear();
}

void SpriteBatch::render(int width, int height)
{
    render(0, width, 0, height);
}

void SpriteBatch::render(int left, int right, int bottom, int top)
{
    glm::mat4 projectionMatrix = glm::ortho((float)left, (float)right, (float)bottom, (float)top, 1.0f, -1.0f);
    glm::mat4 modelViewMatrix = glm::mat4();

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

    
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> opaqueSprites = this->getOpaqueSprites();
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

    std::vector<Sprite*> transparentSprites = this->getTransparentSprites();

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
            range.shader->use();
            glUniformMatrix4fv(range.shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniformMatrix4fv(range.shader->getUniformLocation("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
            glUniform1i(range.shader->getUniformLocation("tex"), 0);

            range.shader->bindArrayBuffer(range.shader->getAttribLocation("vertexPos"), vbo, GL_FLOAT, 3, 3 * sizeof(GLfloat));
            range.shader->bindArrayBuffer(range.shader->getAttribLocation("textureCoords"), tbo, GL_FLOAT, 2, 2 * sizeof(GLfloat));
        
        }
        

        glDrawElements( GL_TRIANGLES, 6 * range.elements, GL_UNSIGNED_INT, (void*) (offset*sizeof(GLuint)));
        offset += 6 * range.elements;

        if(range.transparent)
        {
            glDisable(GL_BLEND);
        }
    }

    GLuint buffers[3] = {vbo, tbo, ibo};
    glDeleteBuffers(3, buffers);
    
    clear();
}