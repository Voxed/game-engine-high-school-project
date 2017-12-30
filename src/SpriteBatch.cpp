#include "SpriteBatch.h"

void SpriteBatch::draw(Sprite sprite)
{
    sprites.push_back(sprite);
}

std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> SpriteBatch::getOrdererdSprites()
{

    //constructing
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> sprites_by_texture_by_shader;
    for(auto &sprite: sprites)
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

    return sprites_by_texture_by_shader;
};