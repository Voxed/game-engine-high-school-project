#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>

class Keyboard
{
    /**
     * @brief The keybinds
     * 
     */
    static std::map<int, std::vector< std::string >> binds;
public:
    /**
     * @brief Bind an action
     * 
     * @param keycode The key to bind it to
     * @param action The action to bind the key to
     */
    static void bindAction(int keycode, std::string action);
    /**
     * @brief Get all actions bound to a key
     * 
     * @param keycode The bound actions
     * @return std::vector<const char*> The actions bound
     */
    static std::vector<std::string> getActions(int keycode);
};

#endif