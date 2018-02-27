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
    int height, width;

public:
    /**
     * @brief Initialize a placeholder spritebatch 
     * 
     * @return A placeholder spritebatch
     */
    SpriteBatch();
    /**
     * @brief Initialize a spritebatch
     * 
     * @return A spritebaatch
     */
    SpriteBatch(int width, int height);
    /**
     * @brief Get a list of opaque sprites sorted
     * 
     * @return A liste of opaque sprites
     */
    std::map<Shader*, std::map<Texture*, std::vector<Sprite*>>> getOpaqueSprites();
    /**
     * @brief Get a list of all transparent sprite
     * 
     * @return std::vector<Sprite*> A list of all transparent sprites
     */
    std::vector<Sprite*> getTransparentSprites();
    /**
     * @brief Draw one sprite to the batch
     * 
     * @param sprite The sprite to draw
     */
    void draw(Sprite s);
    /**
     * @brief Draw multiple sprites to the batch
     * 
     * @param sprites The sprites to draw
     */
    void draw(std::vector<Sprite> s);
    /**
     * @brief Empty the sprite batch
     *
     * And remove all temporary textures
     * 
     */
    void clear();
    /**
     * @brief Render spritebatch to the canvas
     * 
     * @param left The left of the canvas
     * @param right The right of the canvas
     * @param bottom The bottom of the canvas
     * @param top The top of the canvas
     */
    void render(int left, int right, int bottom, int top);
    /**
     * @brief Render spritebatch to the canvas
     * 
     * @param width The width of the canvas
     * @param height The height of the canvas
     */
    void render();
    /**
     * @brief Get the height of the canvas
     * 
     * @return The canvas height as an int
     */
    int getHeight();
    /**
     * @breif Get the width of the canvas
     * 
     * @return The canvas width
     */
    int getWidth();
};
#endif