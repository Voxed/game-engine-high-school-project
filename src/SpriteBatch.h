#ifndef _SPRITE_BATCH_H
#define _SPRITE_BATCH_H
#include "Sprite.h"
#include "Texture.h"
#include <vector>
#include <map>

class SpriteBatch
{
    std::vector<Sprite> sprites;

public:
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> getOrdererdSprites();
    void draw(Sprite s);
};
#endif

/**
 * Chunk
 * shader 
 * texture
 * elemAmount
 **/