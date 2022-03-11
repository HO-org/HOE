#include "raylib.h"
#include "player.h"
#include <iostream>
#include <string>

const int screenWidth = 800;
const int screenHeight = 600;

const float g_FPS_UPDATE_INTERVAL = 0.1f;
float g_TimeSinceUpdatedFPS = 0.0f;

float g_FPS = 0.0f;

Player g_Player = Player();

void Update(double deltaTime);
void Draw(double deltaTime);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Game!");
    SetTargetFPS(5000000000);

    g_Player.Ready(screenWidth, screenHeight);
    // g_Player.m_Texture = LoadTexture("../resources/player.png");
    // g_Player.m_PosX = (float)screenWidth / 2;
    // g_Player.m_PosY = (float)screenHeight / 2;


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

    DrawTexture(g_Player.getTexture(), g_Player.getPosX(), g_Player.getPosY(), WHITE);

    DrawText(TextFormat("FPS: %s", std::to_string((int)g_FPS).c_str()), 50, 50, 24, BLACK);

    EndDrawing();
}