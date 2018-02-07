#include "SpriteFont.h"

/**
 * @brief Initialize empty sprite font
 * 
 */
SpriteFont::SpriteFont() 
{

}

/**
 * @brief Initialize spritefont
 * 
 * @param t A pointer to a texture
 * @param c The letters included in the texture
 * @param cw The row size
 * @param ch The column size
 * @param ls The spacing between letters
 */
SpriteFont::SpriteFont(Texture* t, std::string c, int cw, int ch, int ls)
{
    font_texture = t;
    characters = c;
    characters_row = cw;
    characters_height = ch;
    letter_spacing = ls;
}

/**
 * @brief Get a sprite list from a string
 * 
 * @param text The text to draw
 * @param x The x coordinate
 * @param y The y coordinate
 * @param shader The shader to use
 * @param depth The depth 
 * @param scale The scale
 * @return std::vector<Sprite> A list of sprites representing the text
 */
std::vector<Sprite> SpriteFont::getSprites(std::string text, int x, int y, Shader * shader, float depth, float scale)
{
    std::vector<Sprite> sprites;
    for(int i = 0; i < text.size(); i++)
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

/**
 * @brief Get width of the font
 * 
 * @param length The length of the string to get the width of
 * @param scale The scale
 * @return float The width of the string
 */
float SpriteFont::getWidth(int length, float scale)
{
    float font_width = font_texture->getWidth()/characters_row;
    return length*(font_width+letter_spacing)*scale;
}

/**
 * @brief Get the height of the font
 * 
 * @param scale The scale
 * @return float 
 */
float SpriteFont::getHeight(float scale)
{
    float font_height = font_texture->getHeight()/characters_height;
    return font_height*scale;
}