#include "raylib.h"
#include "player.h"
#include "game.h"
#include <iostream>
#include <string>

const float g_FPS_UPDATE_INTERVAL = 0.1f;
float g_TimeSinceUpdatedFPS = 0.0f;

float g_FPS = 0.0f;

Player g_Player = Player();

Game& g_Game = Game::GetInstance();

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
    g_Game.AddComponent(&g_Player);
    g_Game.AddComponent(&g_Player.m_Sprite);
    g_Game.AddRenderComponents(&g_Player.m_Sprite);
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

    g_Game.DrawComponents();

    DrawText(TextFormat("FPS: %s", std::to_string((int)g_FPS).c_str()), 50, 50, 24, BLACK);

    // int rectWidth = 35;
    // int rectLength = 500;
    // DrawRectangle(((int)g_Game.getScreenWidth() / 2) + 200, ((int)g_Game.getScreenHeight() / 2) - (rectLength / 2), rectWidth, rectLength, RED);
    DrawRectangle(((int)g_Game.getScreenWidth() / 2), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);

    EndDrawing();
}