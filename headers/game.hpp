#include <SDL2/SDL.h>
#include "snake.hpp"

#define MAX_LENGTH 1024

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 840
#define GRID_SIZE 32

class Game
{
private:
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Snake cobra = Snake(16, 16, 3);
    SDL_Rect *bodyRects;
    uint rectSize = WINDOW_HEIGHT / GRID_SIZE;
    SDL_Color defaultWhiteColor;

public:
    bool isRunning = true;
    bool isPaused = false;
    SDL_Event event;
    Game(unsigned int width, unsigned int height);
    void input();
    void update();
    void render();
    void drawRectangle(SDL_Rect *rect, SDL_Color *color);
    void drawAllRectangles(SDL_Rect *rects, uint count, SDL_Color *color);
    ~Game();
};
