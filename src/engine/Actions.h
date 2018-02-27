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
    /**
     * @brief The action event.
     * 
     * Gets called every time an action is called
     * 
     * @param action The action that was called
     * @param delta The current update delta
     */
    virtual void onAction(Action action, float delta);
};

class Actions
{
    /**
     * @brief All the current action listeners
     * 
     */
    static std::vector< ActionListener* > listeners;
public:
    /**
     * @brief Add an action listener
     * 
     * @param l The action listener to be used
     */
    static void addListener(ActionListener* listener);
    /**
     * @brief Remove an action listener
     * 
     * @param l The action listener to be removed
     */
    static void removeListener( ActionListener* );
    /**
     * @brief Call an action
     * 
     * @param action Action
     * @param delta The current update delta
     */
    static void call(Action action, float delta);
};

#endif