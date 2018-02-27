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
    /**
     * @brief Initialize empty sprite font
     * 
     */
    SpriteFont();
    /**
     * @brief Initialize spritefont
     * 
     * @param font_texture A pointer to a texture
     * @param characters The letters included in the texture
     * @param characters_row The row size
     * @param characters_height The column size
     * @param letter_spacing The spacing between letters
     */
    SpriteFont(Texture* font_texture, std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?", int characters_row = 10, int characters_height = 10, int letter_spacing = 0);
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
    std::vector<Sprite> getSprites(std::string text, int x, int y, Shader* shader, float depth = 0.0f, float scale = 1.0f, Color c = Color(0,0,0));
    /**
     * @brief Get width of the font
     * 
     * @param length The length of the string to get the width of
     * @param scale The scale
     * @return float The width of the string
     */
    float getWidth(int length, float scale = 1);
    /**
     * @brief Get the height of the font
     * 
     * @param scale The scale
     * @return float The height of the fonts
     */
    float getHeight(float scale = 1);
};

#endif