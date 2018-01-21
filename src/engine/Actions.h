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
    const char* action;
    ActionType type;
    ActionState state;
};

class ActionListener
{
public:
    virtual void onAction(Action action, float delta);
};

class Actions
{
    static std::vector< ActionListener* > listeners;
public:
    static void addListener(ActionListener* listener);
    static void removeListener( ActionListener* );
    static void call(Action action, float delta);
};

#endif