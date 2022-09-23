#include "../include/headers/game.hpp"
#include <iostream>

Game::Game(unsigned int width, unsigned int height)
{
    defaultWhiteColor = SDL_Color();
    defaultWhiteColor.r = 0xff;
    defaultWhiteColor.g = 0xdd;
    defaultWhiteColor.b = 0x99;
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

    dirChanges = Queue<Direction>(5);

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
        if (!dirChanges.isEmpty())
        {
            cobra.changeDirection(dirChanges.deQueue());
        }

        cobra.moveFoward();

        std::cout << "Tamanho cobra: " << cobra.length << std::endl;
            
        for (int i = 0; i < cobra.length; i++)
        {
            bodyRects[i].x = cobra.body[i].position.x * GRID_SIZE;
            bodyRects[i].y = cobra.body[i].position.y * GRID_SIZE;
            bodyRects[i].h = rectSize;
            bodyRects[i].w = rectSize;
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
        // an event was found
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:

                if ((dirChanges.isEmpty() || dirChanges.rear->value != Up) && !dirChanges.isFull())
                    dirChanges.enQueue(Up);
                break;
            case SDLK_s:
                if ((dirChanges.isEmpty() || dirChanges.rear->value != Down) && !dirChanges.isFull())
                    dirChanges.enQueue(Down);
                break;
            case SDLK_a:
                if ((dirChanges.isEmpty() || dirChanges.rear->value != Left) && !dirChanges.isFull())
                    dirChanges.enQueue(Left);
                break;
            case SDLK_d:
                if ((dirChanges.isEmpty() || dirChanges.rear->value != Right) && !dirChanges.isFull())
                    dirChanges.enQueue(Right);
                break;
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_p:
            cobra.growUp();
                break;
            default:
                break;
            }
        }
    }
}