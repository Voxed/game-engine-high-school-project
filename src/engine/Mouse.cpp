#include "Mouse.h"

std::map<int, std::vector< std::string >> Mouse::binds = std::map<int, std::vector< std::string >>();


int Mouse::getX()
{
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int Mouse::getY()
{
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

void Mouse::bindAction(int mousebutton, std::string action)
{
    if( !binds.count(mousebutton) )
    {
        binds.insert(std::make_pair(mousebutton, std::vector<std::string>()));
    }
    std::vector<std::string>& actions = binds.at(mousebutton);
    if( std::find(actions.begin(), actions.end(), action) == actions.end() )
    {
        actions.push_back(action);
    }
}

std::vector<std::string> Mouse::getActions(int mousebutton)
{
    if( binds.count(mousebutton) )
    {
        return binds.at(mousebutton);
    }
    return std::vector<std::string>();
}