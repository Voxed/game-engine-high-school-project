#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>

class Keyboard
{
    static std::map<int, std::vector< std::string >> binds;
public:
    static void bindAction(int keycode, std::string action);
    static std::vector<std::string> getActions(int keycode);
};

#endif