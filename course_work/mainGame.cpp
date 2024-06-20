#include "Game.h"
int main()
{
    try
    {
        Game::GameInit();
        while (Game::IsOpen())
            Game::Update();
    }
    catch(ExceptionWindowClose& ex)
    {
        ex.processEvent(true);
    }
    catch(ExceptionLongTimeNoActive& ex)
    {
        ex.processEvent(true);
    }
    catch(std::exception& ex)
    {
        std::cerr << "Event 5: Some other exceptions occurred here (" << ex.what() << ")\n";
        Game::windowClose(false);
    }
    return 0;
}