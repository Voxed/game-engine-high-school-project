#include "Mouse.h"

/**
 * @brief Mouse bindings
 * 
 */
std::map<int, std::vector< std::string >> Mouse::binds = std::map<int, std::vector< std::string >>();

/**
 * @brief Get mouse position
 * 
 * @return int x coordinate
 */
int Mouse::getX()
{
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

/**
 * @brief Get mouse position
 * 
 * @return int y coordinate
 */
int Mouse::getY()
{
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

/**
 * @brief Bind an action
 * 
 * @param mousebutton The mousebutton to bind
 * @param action The action to bind
 */
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

/**
 * @brief Get all actions bound to button
 * 
 * @param mousebutton The numbered mousebutton
 * @return std::vector<std::string> All the actions bound to the button
 */
std::vector<std::string> Mouse::getActions(int mousebutton)
{
    if( binds.count(mousebutton) )
    {
        return binds.at(mousebutton);
    }
    return std::vector<std::string>();
}