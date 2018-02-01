#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>

class Keyboard
{
    static std::map<int, std::vector< const char* >> binds;
public:
    static void bindAction(int keycode, const char* action);
    static std::vector<const char*> getActions(int keycode);
};

#endif