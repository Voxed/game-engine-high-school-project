#ifndef _SPRITE_BATCH_H
#define _SPRITE_BATCH_H
#include "Sprite.h"
#include "Texture.h"
#include <vector>
#include <map>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>


class SpriteBatch
{
    std::vector<Sprite> sprites;

public:
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> getOpaqueSprites();
    std::vector<Sprite*> getTransparentSprites();
    void draw(Sprite s);
    void draw(std::vector<Sprite> s);
    void clear();
    void render(int left, int right, int bottom, int top);
    void render(int height, int width);
};
#endif

/**
 * Chunk
 * shader 
 * texture
 * elemAmount
 **/