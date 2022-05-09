#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "game.h"
#include "enums.h"
#include "hf_input.h"
#include <iostream>
#include <string>
#include <string.h>
#include "hflog.h"

static const float g_FPS_UPDATE_INTERVAL = 0.1f;
static float g_TimeSinceUpdatedFPS = 0.0f;
static float g_FPS = 0.0f;

static const double g_PHYSICS_UPDATE_TICK = 1.0 / 144.0;

static Game& g_Game = Game::GetInstance();
static HFLog& g_Logger = HFLog::GetInstance();

extern void HOEINIT_AddComponents();

static void Update(double deltaTime);
static void DrawGame(SDL_Renderer** renderer);
static bool init(SDL_Window** window, SDL_Renderer** renderer);
static void quit(SDL_Renderer** renderer, SDL_Window** window);
static void UpdateFPS(double deltaTime);

int main(int argc, char* args[])
{
    g_Logger.Init(argc, args);
    g_Logger.Log(HFLog::HF_INFO, "HOE starting!", __FILE__, __LINE__);

    g_Game.initalize(800, 600);

    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!init(&window, &renderer))
    {
        g_Logger.Log(HFLog::HF_ERROR, "Failed to init engine!", __FILE__, __LINE__);

        quit(&renderer, &window);
        return 0;
    }

    g_Game.m_CurRenderer = &renderer;

    g_Logger.DLog(HFLog::HF_INFO, "Hooking into game and adding components...", __FILE__, __LINE__);
    HOEINIT_AddComponents();

    g_Logger.DLog(HFLog::HF_INFO, "Initializing components...", __FILE__, __LINE__);
    g_Game.InitComponents();

    g_Logger.DLog(HFLog::HF_INFO, "Calling components ready...", __FILE__, __LINE__);
    g_Game.ReadyComponents();

    g_Logger.DLog(HFLog::HF_INFO, "Initializing time...", __FILE__, __LINE__);
    Uint64 curTime = SDL_GetPerformanceCounter();
    Uint64 lastTime = 0;
    double deltaTime = 0;
    double accumulator = 0;

    bool gameLoop = true;
    g_Logger.Log(HFLog::HF_WARNING, "Game loop starting!", __FILE__, __LINE__);
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
                g_Logger.Log(HFLog::HF_WARNING, "Received quit signal, closing game loop.", __FILE__, __LINE__);
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


static bool init(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        g_Logger.Log(HFLog::HF_ERROR, std::string("Could not init SDL_VIDEO! SDL Error: ") + SDL_GetError(), __FILE__, __LINE__);
        return false;
    }
    
    if (SDL_Init(SDL_INIT_TIMER) < 0)
    {
        g_Logger.Log(HFLog::HF_ERROR, std::string("Could not init SDL_TIMER! SDL Error: ") + SDL_GetError(), __FILE__, __LINE__);
        return false;
    }

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, g_Game.RENDER_SCALE_MODE ) )
    {
        g_Logger.Log(HFLog::HF_WARNING, std::string("Linear texture filtering not enabled!"), __FILE__, __LINE__);
    }

    *window = SDL_CreateWindow("HOEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              g_Game.getScreenWidth(), g_Game.getScreenHeight(), SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        g_Logger.Log(HFLog::HF_ERROR, std::string("Could not create SDL Window! SDL Error: ") + SDL_GetError(), __FILE__, __LINE__);
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        g_Logger.Log(HFLog::HF_ERROR, std::string("Could not create renderer! SDL Error: ") + SDL_GetError(), __FILE__, __LINE__);
        return false;
    }

    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        g_Logger.Log(HFLog::HF_ERROR, std::string("SDL_image could not initialize! SDL_image Error: ") + IMG_GetError(), __FILE__, __LINE__);
        return false;
    }

    if ( TTF_Init() == -1 )
    {
        g_Logger.Log(HFLog::HF_ERROR, std::string("SDL_ttf could not initialize! SDL_ttf Error: ") + TTF_GetError(), __FILE__, __LINE__);
        return false;
    }

    return true;
}


static void quit(SDL_Renderer** renderer, SDL_Window** window)
{
    g_Logger.Log(HFLog::HF_INFO, "Quitting SDL2.", __FILE__, __LINE__);

    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    *window = NULL;
    *renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


static void Update(double deltaTime)
{
    UpdateFPS(deltaTime);
    g_Game.UpdateComponents(deltaTime);
}


static void DrawGame(SDL_Renderer** renderer)
{
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
    SDL_RenderClear(*renderer);

    g_Game.DrawComponents(renderer, true);

    SDL_RenderPresent(*renderer);
}


static void UpdateFPS(double deltaTime)
{
    g_TimeSinceUpdatedFPS += deltaTime;
    if (deltaTime && g_TimeSinceUpdatedFPS > g_FPS_UPDATE_INTERVAL)
    {
        g_FPS = 1 / deltaTime;
        g_TimeSinceUpdatedFPS = 0.0f;
    }
}


