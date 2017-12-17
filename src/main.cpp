#include "Core.h"

class App
{
    Core c;
public:
    int run() 
    {
        c.start();
    };
    bool hasError()
    {
        return c.hasError();
    };
};

int main()
{
    App app;
    if( !app.hasError() )
    {
        return app.run();
    }
    return -1;
}