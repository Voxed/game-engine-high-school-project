#ifndef _MOUSE_H
#define _MOUSE_H

#include <SDL2/SDL.h>
#include <map>
#include <vector> 
#include <algorithm>

class Mouse
{
    static std::map<int, std::vector< std::string >> binds;
public:
    static int getX();
    static int getY();
    static void bindAction(int mousebutton, std::string action);
    static std::vector<std::string> getActions(int mousebutton);
};

#endif