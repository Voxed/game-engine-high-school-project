#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{
    font = Texture("./resources/textures/spritefont.png");
    planet = Texture("./resources/textures/planet.png");
    cloud = Texture("./resources/textures/clouds.png");
    setBackgroundColor(Color(0.25,0.25,0.5));
    shad = Shader::loadShaderFromFile("default");
    if(!shad.isCompiled())
        printf("%s", shad.getErrorString().c_str());
    shad2 = Shader::loadShaderFromFile("toon");
    sf = SpriteFont(&font, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?+-0123456789:", 10, 10, 0 );
    mesh = Mesh("./resources/meshes/planet.obj");

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
    mesh.render(planet, shad, glm::rotate(
        glm::scale(
        glm::translate(glm::mat4(), glm::vec3(75,75,0))
        , glm::vec3(37,37,0.5)),
        rot, glm::vec3(0,1,0.2)));
    mesh.render(cloud, shad, glm::rotate(
        glm::scale(
        glm::translate(glm::mat4(), glm::vec3(75,75,0))
        , glm::vec3(40,40,0.6)),
        rot*5, glm::vec3(0,1,0.2)));
    target.unbind();
    b.draw(Sprite(target.getTexture(), &shad2, 720/2-300, 480/2-300, 0.0f, 4.0f, 4.0f));
    b.draw(sf.getSprites("Voxel Engine: Mesh rendering", 10, 10, &shad, 0.0f, 4.0f));
}

void ScreenMenu::update(float delta)
{
    rot += delta*3.14*2*(1.0f/50) + delta*3.14*2*rot_velocity;
    if(!rotating)
    {
        rot_velocity -= rot_velocity*0.99*delta;
    }
    scale += 0.04;
}

void ScreenMenu::onAction(Action action, float delta)
{
    rotating = false;
    if(action.state == ActionState::HELD)
    {
        if(action.action == "rot_right")
        {
            rot_velocity -= 1.0f*delta;
            rotating = true;
        }
        if(action.action == "rot_left")
        {
            rot_velocity += 1.0f*delta;
            rotating = true;
        }
    }
}