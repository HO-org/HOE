#include "raylib.h"
#include "player.h"
#include "game.h"
#include "enums.h"
#include "raycast.h"
#include "block.h"
#include <iostream>
#include <string>

const float g_FPS_UPDATE_INTERVAL = 0.1f;
float g_TimeSinceUpdatedFPS = 0.0f;

float g_FPS = 0.0f;

Player g_Player = Player();

Game& g_Game = Game::GetInstance();

CollisionComponent g_SquareCollision = CollisionComponent();
CollisionComponent g_SquareCollision2 = CollisionComponent();

const int NUM_BLOCKS = 3;
Block g_LevelBlocks[NUM_BLOCKS] = {
    Block(HFMath::Vector2(1000.0f, 20.0f), HFMath::Vector2(-100, 450)),
    Block(HFMath::Vector2(50.0f, 15.0f), HFMath::Vector2(100, 390)),
    Block(HFMath::Vector2(50.0f, 15.0f), HFMath::Vector2(700, 390))
};

// Raycast g_raycast;

void AddComponentsToGame();
void Update(double deltaTime);
void Draw(double deltaTime);

int main(void)
{
    g_Game.initalize(800, 600);

    InitWindow(g_Game.getScreenWidth(), g_Game.getScreenHeight(), "Raylib Game!");
    // SetTargetFPS(20);

    AddComponentsToGame();

    g_Game.ReadyComponents();

    // g_raycast.m_Transform.SetGlobalPosition(HFMath::Vector2(0.0f, 0.0f));
    // g_raycast.m_Direction = HFMath::Vector2(1.0f, 0.0f);

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


void AddBlocks()
{
    for ( int i = 0; i < NUM_BLOCKS; i++ )
    {
        g_Game.AddComponent(&g_LevelBlocks[i], READY);
        g_Game.AddRenderComponent(&g_LevelBlocks[i]);
        g_Game.AddCollisionComponent(&(g_LevelBlocks[i].m_Collision));
    }
}


void AddComponentsToGame()
{
    g_Game.AddComponent(&g_Player, READYUPDATE);
    g_Game.AddComponent(&g_Player.m_Sprite, READYUPDATE);
    g_Game.AddRenderComponent(&g_Player.m_Sprite);
    g_Game.AddCollisionComponent(&g_Player.m_Collider);

    // g_Game.AddComponent(&g_Floor, READY);
    // g_Game.AddRenderComponent(&g_Floor);
    // g_Game.AddCollisionComponent(&g_Floor.m_Collision);

    AddBlocks();

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


void Draw(double deltaTime)
{
    BeginDrawing();

    ClearBackground(WHITE);

    g_Game.DrawComponents();

    DrawText(TextFormat("FPS: %s", std::to_string((int)g_FPS).c_str()), 50, 50, 24, BLACK);

    EndDrawing();

    // DrawCircle(g_raycast.m_Transform.GetGlobalPosition().GetX(), g_raycast.m_Transform.GetGlobalPosition().GetY(), 10.0f, GREEN);
    // int rectWidth = 35;
    // int rectLength = 500;
    // DrawRectangle(((int)g_Game.getScreenWidth() / 2) + 200, ((int)g_Game.getScreenHeight() / 2) - (rectLength / 2), rectWidth, rectLength, RED);
    // DrawRectangle(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);
    // DrawRectangle(((int)g_Game.getScreenWidth() / 2 - 200), ((int)g_Game.getScreenHeight() / 2), 20, 20, RED);
    
    // HFMath::Vector2 wall1 = HFMath::Vector2(100.0f, 50.0f);
    // HFMath::Vector2 wall2 = HFMath::Vector2(100.0f, -50.0f);
    // HFMath::Vector2 wall1 = HFMath::Vector2(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2));
    // HFMath::Vector2 wall2 = HFMath::Vector2(((int)g_Game.getScreenWidth() / 2 + 200), ((int)g_Game.getScreenHeight() / 2) + 200);

    // g_raycast.m_Transform.SetGlobalPosition(HFMath::Vector2(100.0f, 100.0f));

    // HFMath::Vector2 mousePos = HFMath::Vector2(GetMousePosition().x, GetMousePosition().y);

    // g_raycast.LookAt(mousePos);

    // IntersectResult result = g_raycast.IntersectRay(wall1, wall2);

    // if (result.hit)
    // {
    //     DrawCircle(result.position.GetX(), result.position.GetY(), 30.0f, BLACK);
    //     // std::cout << "Mouse Pos: " << mousePos << std::endl;
    //     // std::cout << "Result Pos: " << result.position << std::endl;
    //     std::cout << (int)result.position.GetY() - mousePos.GetY() << std::endl;
    // }
    
    // DrawLine(wall1.GetX(), wall1.GetY(), wall2.GetX(), wall2.GetY(), ORANGE);

    // RaycastHitResult result = g_raycast.CollideRay(&g_Player.m_Collider, mousePos);
    // // std::cout << mousePos << std::endl;
    // if (result.hit)
    // {
    //     DrawCircle(result.position.GetX(), result.position.GetY(), 15.0f, BLACK);
    //     // std::cout << result.position << std::endl;
    // }

}