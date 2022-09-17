#include "headers/game.hpp"
#include <iostream>

Game::Game(unsigned int width, unsigned int height)
{
    defaultWhiteColor = SDL_Color();
    defaultWhiteColor.r = 0xff;
    defaultWhiteColor.g = 0xff;
    defaultWhiteColor.b = 0xff;
    defaultWhiteColor.a = 0xff;

    // initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // create window
    // set the title bar
    screen = SDL_CreateWindow("My window",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    // Create
    renderer = SDL_CreateRenderer(screen, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    bodyRects = (SDL_Rect *)malloc(MAX_LENGTH * sizeof(SDL_Rect));

    for (int i = 0; i < cobra.length; i++)
    {
        bodyRects[i].x = cobra.body[i].position.x * GRID_SIZE;
        bodyRects[i].y = cobra.body[i].position.y * GRID_SIZE;
        bodyRects[i].w = rectSize;
        bodyRects[i].h = rectSize;
    }
}

void Game::render()
{

    SDL_RenderClear(renderer);

    drawAllRectangles(bodyRects, cobra.length, &defaultWhiteColor);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderPresent(renderer);
}

void Game::update()
{
    if (!isPaused)
    {
        cobra.moveFoward();
        for (int i = 0; i < cobra.length; i++)
        {
            bodyRects[i].x = cobra.body[i].position.x * GRID_SIZE;
            bodyRects[i].y = cobra.body[i].position.y * GRID_SIZE;
        }
    }
}

void Game::drawRectangle(SDL_Rect *rect, SDL_Color *color)
{

    SDL_SetRenderDrawColor(renderer,
                           color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer, rect);
}

void Game::drawAllRectangles(SDL_Rect *rects, uint count, SDL_Color *color)
{

    SDL_SetRenderDrawColor(renderer,
                           color->r, color->g,
                           color->b, color->a);
    SDL_RenderFillRects(renderer, rects, count);
}

Game::~Game()
{
}

void Game::input()
{

    if (SDL_PollEvent(&event))
    {
        // std::cout << "Button pressed " << std::endl;
        // std::cout << "Type: " << event.type << std::endl;
        // std::cout << "Code: " << event.key.keysym.sym << std::endl;

        // an event was found
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                cobra.changeDirection(Up);
                break;
            case SDLK_s:
                cobra.changeDirection(Down);
                break;
            case SDLK_a:
                cobra.changeDirection(Left);
                break;
            case SDLK_d:
                cobra.changeDirection(Right);
                break;
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }
}