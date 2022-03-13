#include "raylib.h"
#include "player.h"
#include "game.h"
#include "enums.h"
#include <iostream>
#include <string>

const float g_FPS_UPDATE_INTERVAL = 0.1f;
float g_TimeSinceUpdatedFPS = 0.0f;

float g_FPS = 0.0f;

Player g_Player = Player();

Game& g_Game = Game::GetInstance();

CollisionComponent g_SquareCollision = CollisionComponent();
CollisionComponent g_SquareCollision2 = CollisionComponent();

void AddComponentsToGame();
void Update(double deltaTime);
void Draw(double deltaTime);

int main(void)
{
    g_Game.initalize(800, 600);

    InitWindow(g_Game.getScreenWidth(), g_Game.getScreenHeight(), "Raylib Game!");
    // SetTargetFPS(144);

    AddComponentsToGame();

    g_Game.ReadyComponents();

    double lastTime = GetTime();

    // Game Loop
    while (!WindowShouldClose())
    {
        double curTime = GetTime();
        double deltaTime = (curTime - lastTime);

        Update(deltaTime);

        Draw(deltaTime);
        
        lastTime = curTime;
    }
}


void AddComponentsToGame()
{
    g_Game.AddComponent(&g_Player, READYUPDATE);
    g_Game.AddComponent(&g_Player, READYUPDATE);
    g_Game.AddComponent(&g_Player.m_Sprite, READYUPDATE);
    g_Game.AddRenderComponent(&g_Player.m_Sprite);
    g_Game.AddCollisionComponent(&g_Player.m_Collider);

    g_SquareCollision.m_Transform.SetGlobalPosition(HFMath::Vector2(g_Game.getScreenWidth() / 2.0f + 200.0f, g_Game.getScreenHeight() / 2));
    g_SquareCollision.m_Size = HFMath::Vector2(20, 20);
    g_SquareCollision2.m_Transform.SetGlobalPosition(HFMath::Vector2(g_Game.getScreenWidth() / 2.0f - 200.0f, g_Game.getScreenHeight() / 2));
    g_SquareCollision2.m_Size = HFMath::Vector2(20, 20);
    g_Game.AddCollisionComponent(&g_SquareCollision);
    g_Game.AddCollisionComponent(&g_SquareCollision2);
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


void Draw(double deltaTime)
{
    BeginDrawing();

    ClearBackground(WHITE);

    int rectWidth = 35;
    int rectLength = 500;
    // DrawRectangle(((int)g_Game.getScreenWidth() / 2) + 200, ((int)g_Game.getScreenHeight() / 2) - (rectLength / 2), rectWidth, rectLength, RED);
    DrawRectangle(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);
    DrawRectangle(((int)g_Game.getScreenWidth() / 2 - 200), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);

    g_Game.DrawComponents();

    DrawText(TextFormat("FPS: %s", std::to_string((int)g_FPS).c_str()), 50, 50, 24, BLACK);

    EndDrawing();
}