#include "SpriteFont.h"

SpriteFont::SpriteFont(Texture* t, std::string c, int fw, int fh, int cw, int ch, int ls)
{
    font_texture = t;
    characters = c;
    font_width = fw;
    font_height = fh;
    characters_row = cw;
    characters_height = ch;
    letter_spacing = ls;
}

std::vector<Sprite> SpriteFont::getSprites(std::string text, int x, int y, Shader * shader, float depth, float scale)
{
    std::vector<Sprite> sprites;
    for(int i; i < text.size(); i++)
    {
        char c = text.at(i);
        int offset = c*(font_width+letter_spacing)*scale;
        sprites.push_back(Sprite(font_texture, shader, x + offset, y, depth, scale, scale));
    }
    return sprites;
}