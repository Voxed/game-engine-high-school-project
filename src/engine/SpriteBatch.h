#ifndef _SPRITE_BATCH_H
#define _SPRITE_BATCH_H
#include "Sprite.h"
#include "Texture.h"
#include <vector>
#include <map>
#include <algorithm>

class SpriteBatch
{
    std::vector<Sprite> sprites;

public:
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> getOpaqueSprites();
    std::vector<Sprite*> getTransparentSprites();
    void draw(Sprite s);
    void draw(std::vector<Sprite> s);
    void clear();
};
#endif

/**
 * Chunk
 * shader 
 * texture
 * elemAmount
 **/