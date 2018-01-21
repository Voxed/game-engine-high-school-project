#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{
    setBackgroundColor(Color(1,1,1));
    font = Texture("./resources/textures/spritefont.png");
    shad = Shader::loadShaderFromFile("default");
    sf = SpriteFont(&font, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?+-0123456789:", 10, 10, 0 );
}

void ScreenMenu::render(SpriteBatch& batch)
{
    std::vector<std::string> buttons = {
        "New Game",
        "Continue",
        "Options"
    };
    for(int i = 0; i < buttons.size(); i++)
    {
        batch.draw(sf.getSprites(buttons[i], core->getWidth()/2 - sf.getWidth(buttons[i].size(), 5.0f)/2,i*(50+sf.getHeight(5.0f))-(sf.getHeight(5.0)+(buttons.size()-1)*(50+sf.getHeight(5.0f)))/2 + core->getHeight()/2,&shad, 0.0f, 5.0f));
    }
}

void ScreenMenu::update(float delta)
{
}

void ScreenMenu::onAction(Action action)
{
}