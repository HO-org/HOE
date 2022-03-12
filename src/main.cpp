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

void Update(double deltaTime);
void Draw(double deltaTime);

int main(void)
{
    g_Game.initalize(800, 600);

    InitWindow(g_Game.getScreenWidth(), g_Game.getScreenHeight(), "Raylib Game!");
    // SetTargetFPS(144);

    g_Player.Ready();

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
    g_Player.Update(deltaTime);
}


void Draw(double deltaTime)
{
    BeginDrawing();

    ClearBackground(WHITE);

    // DrawTexture(g_Player.getTexture(), g_Player.GetPosition().GetX(), g_Player.GetPosition().GetY(), WHITE);

    g_Player.m_Sprite.Draw();

    DrawText(TextFormat("FPS: %s", std::to_string((int)g_FPS).c_str()), 50, 50, 24, BLACK);

    // int rectWidth = 35;
    // int rectLength = 500;
    // DrawRectangle(((int)g_Game.getScreenWidth() / 2) + 200, ((int)g_Game.getScreenHeight() / 2) - (rectLength / 2), rectWidth, rectLength, RED);
    DrawRectangle(((int)g_Game.getScreenWidth() / 2), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);

    EndDrawing();
}