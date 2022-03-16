#include "player.h"
#include "game.h"
#include <iostream>
#include "hflog.h"

void Player::Ready()
{
    // m_Texture = LoadTexture("../resources/player.png");
    // HFLog::Log("Tried loading sprite");
    m_Sprite.Load("../resources/player.png");
    HFMath::Vector2 startPos;
    // startPos.SetX((float)Game::GetInstance().getScreenWidth() / 2);
    // startPos.SetY((float)Game::GetInstance().getScreenHeight() / 2);
    startPos.SetX(400);
    startPos.SetY(300);
    m_Transform.SetGlobalPosition(startPos);

    m_Transform.AddChild(&m_Sprite.m_Transform);

    m_Collider.m_Transform.SetGlobalPosition(HFMath::Vector2(0.0f, 0.0f));
    m_Collider.m_Size.SetX(32.0f);
    m_Collider.m_Size.SetY(32.0f);
    m_Transform.AddChild(&m_Collider.m_Transform);
    m_Transform.AddCollider(&m_Collider);

    // HFMath::Vector2 offset = HFMath::Vector2(50.0f, 50.0f);
    // m_Sprite.m_Transform.SetLocalPosition(m_Sprite.m_Transform.GetGlobalPosition() + offset);
    // std::cout << m_Sprite.m_Transform.GetParent()->GetLocalPosition() << std::endl;
    // std::cout << (m_Sprite.m_Transform.GetParent() == NULL) << std::endl;
    // std::cout << m_Sprite.m_Transform.GetLocalPosition() << std::endl;
}

void Player::Update(double deltaTime)
{
    Move(deltaTime);
}


void Player::Move(double deltaTime)
{
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

    HFMath::Vector2 dirVec = HFMath::Vector2(dirX, dirY);
    dirVec = dirVec.Normalized();
    
    velocity.SetX(dirVec.GetX() * speed * deltaTime);

    if (isOnFloor)
    {
        velocity.SetY(0.0f);

        if(IsKeyPressed(KEY_SPACE))
        {
            velocity.SetY(-jumpForce);
        }
    }

    velocity.SetY(velocity.GetY() + GRAVITY * deltaTime);

    HFMath::Vector2 xOffset = m_Transform.GetGlobalPosition() + HFMath::Vector2(velocity.GetX(), 0.0f);
    m_Transform.MoveAndCollide(xOffset);
    HFMath::Vector2 yOffset = m_Transform.GetGlobalPosition() + HFMath::Vector2(0.0f, velocity.GetY() * deltaTime);
    isOnFloor = m_Transform.MoveAndCollide(yOffset);

    // std::cout << "Direction: " << m_Transform.GetGlobalPosition().directionTo(m_Transform.GetGlobalPosition() + velocity) << std::endl;
    // std::cout << "Direction: " << velocity << std::endl;
    
    // std::cout << m_Collider.GetOverlappingComponents().size() << std::endl;

    // std::cout << "velocity: " << velocity << std::endl;
    // std::cout << "position: " << m_Transform.GetGlobalPosition() << std::endl;
}