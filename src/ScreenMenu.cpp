#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{
    Actions::addListener(this);
    Mouse::bindAction(SDL_BUTTON_LEFT, "click");
}

void ScreenMenu::render(SpriteBatch& batch)
{

}

void ScreenMenu::update(float delta)
{
    "Fuck you"
}

void ScreenMenu::onAction(Action action)
{
    if(action.type == ActionType::MOUSE && action.state == ActionState::RELEASED)
    {
        printf("Clicked at %u, %u!\n", Mouse::getX(), Mouse::getY());
    }
}