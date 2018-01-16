#include "Screen.h"

void Screen::render(SpriteBatch& batch)
{
    //Maybe some fun generic screen?
    puts("yo");
}

void Screen::update(float delta)
{

}

void Screen::setBackgroundColor(Color color)
{
    backgroundColor = color;
    if(core->hasStarted())
    {
        glClearColor( color.r, color.g, color.b, color.a );
    }
}

Color Screen::getBackgroundColor()
{
    return backgroundColor;
}