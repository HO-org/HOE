#include "player.h"


void Player::Update(double deltaTime)
{
    float speed = 100.0f;

    float dirX = 0.0f;
    float dirY = 0.0f;

    if (IsKeyDown(KEY_D))
    {
        dirX += 1.0f;
    }
    if (IsKeyDown(KEY_A))
    {
        dirX -= 1.0f;
    }
    if (IsKeyDown(KEY_W))
    {
        dirY += 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        dirY -= 1.0f;
    }

    m_PosX += dirX * speed * deltaTime;
    m_PosY -= dirY * speed * deltaTime;
}


void Player::Ready(int screenWidth, int screenHeight)
{
    m_Texture = LoadTexture("../resources/player.png");
    m_PosX = (float)screenWidth / 2;
    m_PosY = (float)screenHeight / 2;
}