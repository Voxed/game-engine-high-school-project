#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{
    Actions::addListener(this);
    Mouse::bindAction(SDL_BUTTON_LEFT, "click");

    text = Texture("./resources/textures/lol.png");
    shad = Shader::loadShaderFromFile("default");
}

void ScreenMenu::render(SpriteBatch& batch)
{

    batch.draw(Sprite(&text,&shad,50,50));
}

void ScreenMenu::update(float delta)
{
}

void ScreenMenu::onAction(Action action)
{
    if(action.type == ActionType::MOUSE && action.state == ActionState::RELEASED)
    {
        printf("Clicked at %u, %u!\n", Mouse::getX(), Mouse::getY());
    }
}