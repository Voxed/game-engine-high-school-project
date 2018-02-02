#include "ScreenMenu.h"

ScreenMenu::ScreenMenu()
{
    fontTexture = Texture("./resources/textures/spritefont.png");
    //planetTexture = Texture("./resources/textures/planet.png");
    backgroundColor = Color(0.0,0.0,0.1);
    
    defaultShader = Shader::loadShaderFromFile("default");
    if(!defaultShader.isCompiled())
        printf("%s\n", defaultShader.getErrorString().c_str());
    lightShader = Shader::loadShaderFromFile("light");
    
    spritefont = SpriteFont(&fontTexture, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?+-0123456789:", 10, 10, 0 );
    sphereMesh = Mesh("./resources/meshes/planet.obj");
    starTexture = Texture({Color(1,1,1)},1,1,GL_RGB);

    float planetSeed = SDL_GetPerformanceCounter() % 9999;
    float cloudSeed = SDL_GetPerformanceCounter() % 9999;
    planetTexture = Noise::generatePerlin(128,128,8, {0.5,0.6,1.0}, {Color(0.4,0.4,1.0), Color(0.75,0.75,0.5), Color(0.25,0.75,0.25)}, planetSeed);
    planetLightTexture = Noise::generatePerlin(128,128,8, {0.5,1.0}, {Color(0.5,0.5,1.0), Color(0.5,1.0,0.5)}, planetSeed);
    cloudsTexture = Noise::generatePerlin(128,128,4, {0.3, 1.0}, {Color(0.8,0.8,0.8), Color(1,1,1,0.0)}, cloudSeed);
    cloudsLightTexture =  Noise::generatePerlin(128,128,4, {0.3, 1.0}, {Color(1.0,1.0,1.0), Color(0,0,0,0.0)}, cloudSeed);

    Keyboard::bindAction(SDLK_d, "rot_right");
    Keyboard::bindAction(SDLK_a, "rot_left");
    Actions::addListener(this);


    while(stars.size() < 100)
    {
        Star s;
        s.x = rand() % 720;
        s.y = rand() % 480;
        s.v = (rand() % 10) +10;
        stars.push_back(s);
    }  

    Texture lightMap;
}

ScreenMenu::~ScreenMenu()
{
}

void ScreenMenu::render(SpriteBatch& b)
{
    RenderTarget target = RenderTarget(150,150);
    target.bind();
    sphereMesh.render(planetTexture, defaultShader, glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(75,75,0)), glm::vec3(37,37,0.5)),planetRotation, glm::vec3(0,1,0.2)));
    sphereMesh.render(cloudsTexture, defaultShader, glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(75,75,0)), glm::vec3(39,39,0.6)),planetRotation*5, glm::vec3(0,1,0.2)));
    target.unbind();

    lightMap.remove();
    RenderTarget lightMapTarget = RenderTarget(150,150);
    lightMapTarget.bind();
    sphereMesh.render(planetLightTexture, defaultShader, glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(75,75,0)), glm::vec3(37,37,0.5)),planetRotation, glm::vec3(0,1,0.2)));
    sphereMesh.render(cloudsLightTexture, defaultShader, glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(75,75,0)), glm::vec3(39,39,0.6)),planetRotation*5, glm::vec3(0,1,0.2)));
    lightMapTarget.unbind();
    lightMap = lightMapTarget.getTexture();

    lightShader.bindTexture(1, "lightMap", lightMap);
    b.draw(Sprite(target.getTexture(), &lightShader, 720/2-300, 480/2-300, 0.0f, 4.0f, 4.0f, 0, 0, 0, Color(1,1,1), true));
    //b.draw(Sprite(lightMap, &defaultShader, 720/2-300, 480/2-300, 0.0f, 4.0f, 4.0f));
    b.draw(spritefont.getSprites("Voxel Engine: Mesh rendering", 10, 10, &defaultShader, 0.0f, 4.0f));
    b.draw(spritefont.getSprites("FPS: " + std::to_string(core->getFPS()), 10, 10 + 8*4, &defaultShader, 0.0f, 4.0f));
}

void ScreenMenu::update(float delta)
{
    planetRotation += delta*3.14*2*(1.0f/50) + delta*3.14*2*rotationVelocity;
    if(!isRotating)
    {
        rotationVelocity -= rotationVelocity*0.99*delta;
    }

    std::vector<Star> newStars;
    for(Star s : stars)
    {
        s.y += s.v/10*4*delta + s.v/10*4*delta*rotationVelocity*50;
        if(s.y > 480)
        {
            s.y = 0;
            s.x = rand() % 720;
            s.v = (rand() % 10) + 10;
        }
        if(s.y < 0)
        {
            s.y = 480;
            s.x = rand() % 720;
            s.v = (rand() % 10) + 10;
        }
        newStars.push_back(s);
    }
    stars = newStars;
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