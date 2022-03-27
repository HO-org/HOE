#include "SDL.h"
#include "SDL_image.h"
// #include "raylib.h"
#include "player.h"
#include "game.h"
#include "enums.h"
#include "raycast.h"
#include "block.h"
#include "hf_input.h"
#include <iostream>
#include <string>
#include <string.h>
#include "level_loader.h"

const float g_FPS_UPDATE_INTERVAL = 0.1f;
float g_TimeSinceUpdatedFPS = 0.0f;
float g_FPS = 0.0f;

const double g_PHYSICS_UPDATE_TICK = 1.0 / 144.0;

Player g_Player = Player();

Sprite g_Sprite;

Game& g_Game = Game::GetInstance();

// CollisionComponent g_SquareCollision = CollisionComponent();
// CollisionComponent g_SquareCollision2 = CollisionComponent();

const int NUM_BLOCKS = 3;
// Block g_LevelBlocks[NUM_BLOCKS] = {
//     Block(HFMath::Vector2(1000.0f, 20.0f), HFMath::Vector2(-100, 450)),
//     Block(HFMath::Vector2(50.0f, 15.0f), HFMath::Vector2(100, 390)),
//     Block(HFMath::Vector2(50.0f, 15.0f), HFMath::Vector2(700, 390))
// };

std::vector<Block> g_Blocks;

// Raycast g_raycast;

void AddComponentsToGame();
void Update(double deltaTime);
void DrawGame(SDL_Renderer** renderer);
bool init(SDL_Window** window, SDL_Renderer** renderer);
void quit(SDL_Renderer** renderer, SDL_Window** window);
bool loadResources(SDL_Renderer** renderer);

void RaylibDraw();
void RaylibLoop();

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

    if (!loadResources(&renderer))
    {
        quit(&renderer, &window);
        return 0;
    }

    g_Game.m_CurRenderer = &renderer;

    AddComponentsToGame();
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


bool loadResources(SDL_Renderer** renderer)
{
	if (!g_Sprite.load(renderer, "resources/player.png"))
    {
        printf("Failed to load texture!\n");
        return false;
    }

	return true;
}


void AddBlocks()
{
    // for ( int i = 0; i < NUM_BLOCKS; i++ )
    // {
    //     // g_Game.AddComponentCallback(&g_LevelBlocks[i], READY);
    //     // g_Game.AddRenderComponent(&g_LevelBlocks[i]);
    //     // g_Game.AddCollisionComponent(&(g_LevelBlocks[i].m_Collision));
    //     g_Game.AddComponent(&g_LevelBlocks[i]);
    // }

    LevelLoader loader = LevelLoader(24);
    char path[80];
    sprintf(path, "%s/resources/level.hfl", SDL_GetBasePath());
    g_Blocks = loader.loadBlocks(path, '#');

    HFMath::Vector2 offset = HFMath::Vector2(-8, 0);

    for (int i = 0; i < g_Blocks.size(); i++)
    {
        g_Blocks[i].m_Transform.SetGlobalPosition(g_Blocks[i].m_Transform.GetGlobalPosition() + offset);
        g_Game.AddComponent(&g_Blocks[i]);
    }
}


void AddComponentsToGame()
{
    g_Game.AddComponent(&g_Player);
    AddBlocks();

    // g_Game.AddComponentCallback(&g_Player, READYUPDATE);
    // g_Game.AddComponentCallback(&g_Player.m_Sprite, READYUPDATE);
    // g_Game.AddRenderComponent(&g_Player.m_Sprite);
    // g_Game.AddCollisionComponent(&g_Player.m_Collider);

    // g_Game.AddComponentCallback(&g_Floor, READY);
    // g_Game.AddRenderComponent(&g_Floor);
    // g_Game.AddCollisionComponent(&g_Floor.m_Collision);


    // g_SquareCollision.m_Transform.SetGlobalPosition(HFMath::Vector2(g_Game.getScreenWidth() / 2.0f + 200.0f, g_Game.getScreenHeight() / 2));
    // g_SquareCollision.m_Size = HFMath::Vector2(20, 20);
    // g_SquareCollision2.m_Transform.SetGlobalPosition(HFMath::Vector2(g_Game.getScreenWidth() / 2.0f - 200.0f, g_Game.getScreenHeight() / 2));
    // g_SquareCollision2.m_Size = HFMath::Vector2(20, 20);
    // g_Game.AddCollisionComponent(&g_SquareCollision);
    // g_Game.AddCollisionComponent(&g_SquareCollision2);
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

void Update(double deltaTime)
{
    UpdateFPS(deltaTime);
    g_Game.UpdateComponents(deltaTime);
}


void DrawGame(SDL_Renderer** renderer)
{
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
    SDL_RenderClear(*renderer);

    // int centerX = g_Game.getScreenWidth() / 2 - g_Sprite.getWidth();
    // int centerY = g_Game.getScreenHeight() / 2 - g_Sprite.getHeight();
    // g_Sprite.draw(*renderer, centerX, centerY);
    // int posX = (int)(spritePos.GetX());
    // int posY = (int)(spritePos.GetY());
    // std::cout << posX << ", " << posY << "\n";
    // g_Sprite.draw(*renderer);

    // g_Player.m_Sprite.Draw(renderer);
    g_Game.DrawComponents(renderer);
    // std::cout << g_Player.m_Sprite.m_Transform.GetGlobalPosition() << "\n";

    SDL_RenderPresent(*renderer);
}


// void RaylibLoop()
// {
//     g_Game.initalize(800, 600);

//     InitWindow(g_Game.getScreenWidth(), g_Game.getScreenHeight(), "Raylib Game!");
//     SetTargetFPS(400);
//     // SetTargetFPS(20);

//     AddComponentsToGame();
//     g_Game.InitComponents();

//     g_Game.ReadyComponents();

//     // g_raycast.m_Transform.SetGlobalPosition(HFMath::Vector2(0.0f, 0.0f));
//     // g_raycast.m_Direction = HFMath::Vector2(1.0f, 0.0f);

//     double lastTime = GetTime();

//     // Game Loop
//     while (!WindowShouldClose())
//     {
//         double curTime = GetTime();
//         double deltaTime = (curTime - lastTime);

//         Update(deltaTime);

//         RaylibDraw();
        
//         lastTime = curTime;
//     }
// }

// void RaylibDraw(double deltaTime)
// {
//     BeginDrawing();

//     ClearBackground(WHITE);

//     g_Game.DrawComponents();

//     DrawText(TextFormat("FPS: %s", std::to_string((int)g_FPS).c_str()), 50, 50, 24, BLACK);

//     EndDrawing();

//     // DrawCircle(g_raycast.m_Transform.GetGlobalPosition().GetX(), g_raycast.m_Transform.GetGlobalPosition().GetY(), 10.0f, GREEN);
//     // int rectWidth = 35;
//     // int rectLength = 500;
//     // DrawRectangle(((int)g_Game.getScreenWidth() / 2) + 200, ((int)g_Game.getScreenHeight() / 2) - (rectLength / 2), rectWidth, rectLength, RED);
//     // DrawRectangle(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);
//     // DrawRectangle(((int)g_Game.getScreenWidth() / 2 - 200), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);
    
//     // HFMath::Vector2 wall1 = HFMath::Vector2(100.0f, 50.0f);
//     // HFMath::Vector2 wall2 = HFMath::Vector2(100.0f, -50.0f);
//     // HFMath::Vector2 wall1 = HFMath::Vector2(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2));
//     // HFMath::Vector2 wall2 = HFMath::Vector2(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2) + 200);

//     // g_raycast.m_Transform.SetGlobalPosition(HFMath::Vector2(100.0f, 100.0f));

//     // HFMath::Vector2 mousePos = HFMath::Vector2(GetMousePosition().x, GetMousePosition().y);

//     // g_raycast.LookAt(mousePos);

//     // IntersectResult result = g_raycast.IntersectRay(wall1, wall2);

//     // if (result.hit)
//     // {
//     //     DrawCircle(result.position.GetX(), result.position.GetY(), 30.0f, BLACK);
//     //     // std::cout << "Mouse Pos: " << mousePos << std::endl;
//     //     // std::cout << "Result Pos: " << result.position << std::endl;
//     //     std::cout << (int)result.position.GetY() - mousePos.GetY() << std::endl;
//     // }
    
//     // DrawLine(wall1.GetX(), wall1.GetY(), wall2.GetX(), wall2.GetY(), ORANGE);

//     // RaycastHitResult result = g_raycast.CollideRay(&g_Player.m_Collider, mousePos);
//     // // std::cout << mousePos << std::endl;
//     // if (result.hit)
//     // {
//     //     DrawCircle(result.position.GetX(), result.position.GetY(), 15.0f, BLACK);
//     //     // std::cout << result.position << std::endl;
//     // }

// }