#ifndef _MOUSE_H
#define _MOUSE_H

#include <SDL2/SDL.h>
#include <map>
#include <vector> 
#include <algorithm>

class Mouse
{
    /**
     * @brief Mouse bindings
     * 
     */
    static std::map<int, std::vector< std::string >> binds;
public:
    /**
     * @brief Get mouse position
     * 
     * @return int x coordinate
     */
    static int getX();
    /**
     * @brief Get mouse position
     * 
     * @return int y coordinate
     */
    static int getY();
    /**
     * @brief Bind an action
     * 
     * @param mousebutton The mousebutton to bind
     * @param action The action to bind
     */
    static void bindAction(int mousebutton, std::string action);
    /**
     * @brief Get all actions bound to button
     * 
     * @param mousebutton The numbered mousebutton
     * @return std::vector<std::string> All the actions bound to the button
     */
    static std::vector<std::string> getActions(int mousebutton);
};

#endif