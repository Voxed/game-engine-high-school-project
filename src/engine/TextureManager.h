#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include "Texture.h"
#include <string>
#include <vector>
#include <map>

class TextureManager
{
    static void require(std::vector<std::string>);
    static TextureManager & getInstance();
    static Texture & get(std::string name);
    static void load(std::string filenName);

    std::map<std::string, Texture> textures;
};

#endif