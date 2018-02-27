#include "GameScreen.h"

GameScreen::GameScreen()
{
    backgroundColor = Color(0,0,0);
    fontTexture = Texture("./resources/textures/retro_spritefont.png");
    spriteFont = SpriteFont(&fontTexture, "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.!?1234567890");
    logoTexture = Texture("./resources/textures/logo.png");
    defaultShader = Shader::loadShaderFromFile("default");

    world.addSystem<PlayerSystem>(UPDATE_SYSTEM | RENDER_SYSTEM | ACTION_SYSTEM); //Add a new system with access to all of the functionality.


    Actions::addListener(this);
}

GameScreen::~GameScreen()
{
    
}

void GameScreen::render(SpriteBatch& batch)
{
    int innerHeight = 400;
    int innerWidth = 300;
    RenderTarget target = RenderTarget(innerWidth, innerHeight);
    target.bind();
    SpriteBatch b = SpriteBatch(innerWidth, innerHeight);
    //Render logo and coin tip
    b.draw(Sprite(&logoTexture, &defaultShader, b.getWidth()/2 - logoTexture.getWidth()/2, b.getHeight()*0.25-logoTexture.getHeight()/2, 0.9));
    b.draw(spriteFont.getSprites("INSERT COIN TO PLAY!",
        b.getWidth()/2 - spriteFont.getWidth(std::string("INSERT COIN TO PLAY!").size())/2,
        b.getHeight()*0.8-spriteFont.getHeight()+cos(millis()/(1000.0f*0.25f))*5,
        &defaultShader,0.9,1,Color(0.5,1,1)));
    //Render game
    world.render(b);
    b.render();
    target.unbind();
    float dpi = core->getHeight()/(float)innerHeight;
    batch.draw(Sprite(target.getTexture(), &defaultShader, core->getWidth()/2 - innerWidth*dpi/2,0, 0, dpi, dpi));
    target.remove();
}

void GameScreen::update(float delta)
{
    world.update(delta);
    
}

void GameScreen::onAction(Action action, float delta)
{
    world.emitAction(action, delta);
}