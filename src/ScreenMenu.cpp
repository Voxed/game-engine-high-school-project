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
    if(SDL_GetTicks()%1000 > 900)
        fps = core->getFPS();
    batch.draw(sf.getSprites("FPS: " + std::to_string(fps), 10,10,&shad, 0.0f, 2.0f));

    batch.draw(Sprite(&text,&shad,50,50));
    batch.draw(Sprite(&text2,&shad,150,50, 0.0f, 2.0f, 2.0f, true));
}

void ScreenMenu::update(float delta)
{
    x+= delta;
}

void ScreenMenu::onAction(Action action)
{
}