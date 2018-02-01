#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{
    fontTexture = Texture("./resources/textures/spritefont.png");
    planetTexture = Texture("./resources/textures/planet.png");
    cloudsTexture = Texture("./resources/textures/clouds.png");
    setBackgroundColor(Color(0.25,0.25,0.5));
    defaultShader = Shader::loadShaderFromFile("default");
    toonShader = Shader::loadShaderFromFile("toon");
    spritefont = SpriteFont(&fontTexture, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?+-0123456789:", 10, 10, 0 );
    sphereMesh = Mesh("./resources/meshes/planet.obj");

    Keyboard::bindAction(SDLK_d, "rot_right");
    Keyboard::bindAction(SDLK_a, "rot_left");
    Actions::addListener(this);
}

ScreenMenu::~ScreenMenu()
{
}

void ScreenMenu::render(SpriteBatch& b)
{
    RenderTarget target(150,150);
    target.bind();
    sphereMesh.render(planetTexture, defaultShader, glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(75,75,0)), glm::vec3(37,37,0.5)),planetRotation, glm::vec3(0,1,0.2)));
    sphereMesh.render(cloudsTexture, defaultShader, glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(75,75,0)), glm::vec3(40,40,0.6)),planetRotation*5, glm::vec3(0,1,0.2)));
    target.unbind();
    b.draw(Sprite(target.getTexture(), &toonShader, 720/2-300, 480/2-300, 0.0f, 4.0f, 4.0f));
    b.draw(spritefont.getSprites("Voxel Engine: Mesh rendering", 10, 10, &defaultShader, 0.0f, 4.0f));
}

void ScreenMenu::update(float delta)
{
    planetRotation += delta*3.14*2*(1.0f/50) + delta*3.14*2*rotationVelocity;
    if(!isRotating)
    {
        rotationVelocity -= rotationVelocity*0.99*delta;
    }
}

void ScreenMenu::onAction(Action action, float delta)
{
    isRotating = false;
    if(action.state == ActionState::HELD)
    {
        if(action.action == "rot_right")
        {
            rotationVelocity -= 1.0f*delta;
            isRotating = true;
        }
        if(action.action == "rot_left")
        {
            rotationVelocity += 1.0f*delta;
            isRotating = true;
        }
    }
}