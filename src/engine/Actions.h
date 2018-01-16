#ifndef _ACTIONS_H
#define _ACTIONS_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

enum ActionState
{
    HELD,
    PRESSED,
    RELEASED
};

enum ActionType
{
    MOUSE,
    KEYBOARD
};

struct Action
{
    std::string action;
    ActionType type;
    ActionState state;
};

class ActionListener
{
public:
    virtual void onAction(Action action);
};

class Actions
{
    static std::vector< ActionListener* > listeners;
public:
    static void addListener(ActionListener* listener);
    static void removeListener( ActionListener* );
    static void call(Action action);
};

#endif