#include <iostream>
#include "headers/game.hpp"

int main()
{
    Game game = Game(1280, 720);
    double UPDATES_PER_SEC = 5;
    double targetUpdateFrameTime = (1 / UPDATES_PER_SEC) * 1000;
    double ellapsedMs;
    double lag = 0;
    Uint64 now;
    Uint64 before = SDL_GetTicks64();

    while (game.event.type != SDL_QUIT && game.isRunning == true)
    {
        now = SDL_GetTicks();
        ellapsedMs = now - before;

        before = now;
        lag += ellapsedMs;

        game.input();

        while (lag >= targetUpdateFrameTime)
        {
            game.update();
            std::cout << "Time since last update: " << lag << std::endl;
            lag -= targetUpdateFrameTime;
        }

        game.render();
    }
    return 0;
}
