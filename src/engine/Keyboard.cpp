#include "Keyboard.h"

std::map<int, std::vector< std::string >> Keyboard::binds = std::map<int, std::vector< std::string >>();

void Keyboard::bindAction(int keycode, std::string action)
{
    if( !binds.count(keycode) )
    {
        binds.insert(std::make_pair(keycode, std::vector<std::string>()));
    }
    std::vector<std::string>& actions = binds.at(keycode);
    if( std::find(actions.begin(), actions.end(), action) == actions.end() )
    {
        actions.push_back(action);
    }
}

std::vector<std::string> Keyboard::getActions(int keycode)
{
    if( binds.count(keycode) )
    {
        return binds.at(keycode);
    }
    return std::vector<std::string>();
}