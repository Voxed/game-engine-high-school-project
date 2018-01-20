#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{

    text = Texture("./resources/textures/lol.png");
    text2 = Texture("./resources/textures/demon.png");
    font = Texture("./resources/textures/spritefont.png");
    shad = Shader::loadShaderFromFile("default");
    sf = SpriteFont(&font, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?+-0123456789:", 10, 10, 0 );
}

void ScreenMenu::render(SpriteBatch& batch)
{
    batch.draw(sf.getSprites("FPS: " + std::to_string(core->getFPS()), 5,5,&shad, 0.0f, 5.0f));

    batch.draw(Sprite(&text,&shad,50,50));
    for(int i = 0; i < 2000; i++)
    {
        batch.draw(Sprite(&text2,&shad,1000+cos(i)*500,50+floor(i/5), 0.0f, 0.25f, 0.25f, false));
    }
}

void ScreenMenu::update(float delta)
{
    x+= delta;
}

void ScreenMenu::onAction(Action action)
{
}