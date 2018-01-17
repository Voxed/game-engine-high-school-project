#include "SpriteFont.h"

SpriteFont::SpriteFont(Texture* t, std::string c, int cw, int ch, int ls)
{
    font_texture = t;
    characters = c;
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
        if(c != ' ')
        {
            float font_width = font_texture->getWidth()/characters_row;
            float font_height = font_texture->getHeight()/characters_height;
            int offset = i*(font_width+letter_spacing)*scale;
            int index = characters.find(c);
            float subX = (index%characters_row)/(float)characters_row;
            float subY = floor(index/characters_height)/characters_height;
            float subW = font_width/font_texture->getWidth();
            float subH = font_height/font_texture->getHeight();            

            sprites.push_back(Sprite(font_texture, shader, x + offset, y, subX, subY, subW, subH, depth, scale, scale));
        }
    }
    return sprites;
}