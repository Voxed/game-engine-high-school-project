#include "Keyboard.h"

/**
 * @brief The keybinds
 * 
 */
std::map<int, std::vector< const char* >> Keyboard::binds = std::map<int, std::vector< const char* >>();

/**
 * @brief Bind an action
 * 
 * @param keycode The key to bind it to
 * @param action The action to bind the key to
 */
void Keyboard::bindAction(int keycode, const char* action)
{
    if( !binds.count(keycode) )
    {
        binds.insert(std::make_pair(keycode, std::vector<const char*>()));
    }
    std::vector<const char*>& actions = binds.at(keycode);
    if( std::find(actions.begin(), actions.end(), action) == actions.end() )
    {
        actions.push_back(action);
    }
}

/**
 * @brief Get all actions bound to a key
 * 
 * @param keycode The bound actions
 * @return std::vector<const char*> The actions bound
 */
std::vector<const char*> Keyboard::getActions(int keycode)
{
    if( binds.count(keycode) )
    {
        return binds.at(keycode);
    }
    return std::vector<const char*>();
}