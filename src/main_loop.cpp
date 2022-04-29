#include "SDL.h"
#include "SDL_image.h"
#include "game.h"
#include "enums.h"
#include "hf_input.h"
#include <iostream>
#include <string>
#include <string.h>

const float g_FPS_UPDATE_INTERVAL = 0.1f;
float g_TimeSinceUpdatedFPS = 0.0f;
float g_FPS = 0.0f;

const double g_PHYSICS_UPDATE_TICK = 1.0 / 144.0;

static Game& g_Game = Game::GetInstance();

extern void HOEINIT_AddComponents();
void Update(double deltaTime);
void DrawGame(SDL_Renderer** renderer);
bool init(SDL_Window** window, SDL_Renderer** renderer);
void quit(SDL_Renderer** renderer, SDL_Window** window);

int main(int argv, char** args)
{
    g_Game.initalize(800, 600);

    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!init(&window, &renderer))
    {
        quit(&renderer, &window);
        return 0;
    }

    g_Game.m_CurRenderer = &renderer;

    HOEINIT_AddComponents();
    g_Game.InitComponents();

    g_Game.ReadyComponents();

    Uint64 curTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    double deltaTime = 0;
    double accumulator = 0;

    bool gameLoop = true;
    // Game Loop
    while (gameLoop)
    {
        lastTime = curTime;
        curTime = SDL_GetPerformanceCounter();


        deltaTime = ((curTime - lastTime) / (double)SDL_GetPerformanceFrequency() );
        if (deltaTime >= 0.25) { deltaTime = 0.25f; }
        accumulator += deltaTime;

        while (accumulator >= g_PHYSICS_UPDATE_TICK)
        {
            HFInput& inputSystem = HFInput::GetInstance();

            inputSystem.UpdateDownKeys();
            if (inputSystem.m_Quit)
            {
                gameLoop = false;
            }

            g_Game.PhysicsUpdateComponents(g_PHYSICS_UPDATE_TICK);
            accumulator -= g_PHYSICS_UPDATE_TICK;
        }
        
        // Update(deltaTime);

        DrawGame(&renderer);

        // SDL_Delay(2);
    }

    return 0;
}


bool init(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "Could not init SDL_VIDEO! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (SDL_Init(SDL_INIT_TIMER) < 0)
    {
        printf( "Could not init SDL_TIMER! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    *window = SDL_CreateWindow("HOEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              g_Game.getScreenWidth(), g_Game.getScreenHeight(), SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        printf("Could not create SDL Window! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        printf("Could not create renderer! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    return true;
}


void quit(SDL_Renderer** renderer, SDL_Window** window)
{
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    *window = NULL;
    *renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}


void Update(double deltaTime)
{
    UpdateFPS(deltaTime);
    g_Game.UpdateComponents(deltaTime);
}


void DrawGame(SDL_Renderer** renderer)
{
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
    SDL_RenderClear(*renderer);

    g_Game.DrawComponents(renderer);

    SDL_RenderPresent(*renderer);
}


void UpdateFPS(double deltaTime)
{
    g_TimeSinceUpdatedFPS += deltaTime;
    if (deltaTime && g_TimeSinceUpdatedFPS > g_FPS_UPDATE_INTERVAL)
    {
        g_FPS = 1 / deltaTime;
        g_TimeSinceUpdatedFPS = 0.0f;
    }
}


