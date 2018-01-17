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
    sprites.clear();
}