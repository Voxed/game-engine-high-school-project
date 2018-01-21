#ifndef _SPRITE_FONT_H
#define _SPRITE_FONT_H

#include "Texture.h"
#include "Sprite.h"
#include <vector>
#include <string>
#include <tgmath.h>

class SpriteFont
{
    Texture* font_texture;
    std::string characters;
    int characters_row;
    int characters_height;
    int letter_spacing;
public:
    SpriteFont();
    SpriteFont(Texture* font_texture, std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?", int characters_row = 10, int characters_height = 10, int letter_spacing = 0);
    std::vector<Sprite> getSprites(std::string text, int x, int y, Shader* shader, float depth = 0.0f, float scale = 1.0f);
    float getWidth(int length, float scale = 1);
    float getHeight(float scale);
};

#endif