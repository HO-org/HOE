#include "player.h"
#include "game.h"
#include <iostream>
#include "hflog.h"
#include "hf_input.h"
#include <math.h>

void Player::Init()
{
    Game& game = Game::GetInstance();

    game.AddComponentCallback(this, READYUPDATE);
    game.AddComponentCallback(&m_Sprite, READYUPDATE);
    game.AddRenderComponent(&m_Sprite);
    game.AddCollisionComponent(&m_Collider);
}

void Player::Ready()
{
    // m_Texture = LoadTexture("../resources/player.png");
    // HFLog::Log("Tried loading sprite");
    // m_Sprite.Load("resources/player.png");
    // startPos.SetX((float)Game::GetInstance().getScreenWidth() / 2);
    // startPos.SetY((float)Game::GetInstance().getScreenHeight() / 2);
    HFMath::Vector2 startPos;
    startPos.SetX(400);
    startPos.SetY(300);
    m_Transform.SetGlobalPosition(startPos);

    m_Sprite.load(Game::GetInstance().m_CurRenderer, "resources/player.png");
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
    
    // DirectionalMove(deltaTime);
    PlatformerMove(deltaTime);

    // std::cout << "Direction: " << m_Transform.GetGlobalPosition().directionTo(m_Transform.GetGlobalPosition() + velocity) << std::endl;
    // std::cout << "Direction: " << velocity << std::endl;
    
    // std::cout << m_Collider.GetOverlappingComponents().size() << std::endl;

    // std::cout << "velocity: " << velocity << std::endl;
    // std::cout << "position: " << m_Transform.GetGlobalPosition() << std::endl;
}

void Player::PlatformerMove(double deltaTime)
{
    float dirX = 0.0f;
    float dirY = 0.0f;

    HFInput& inputSystem = HFInput::GetInstance();

    if (inputSystem.IsKeyDown(SDLK_d))
    {
        dirX += 1.0f;
    }
    if (inputSystem.IsKeyDown(SDLK_a))
    {
        dirX -= 1.0f;
    }
    

    HFMath::Vector2 dirVec = HFMath::Vector2(dirX, dirY);
    dirVec = dirVec.Normalized();
    
    // velocity.SetX(dirVec.GetX() * m_MaxSpeed * deltaTime);
    if (!dirX || abs(velocity.GetX()) > m_MaxSpeed)
    {
        // velocity.SetX(velocity.GetX() - m_Acceleration * deltaTime);
        velocity.SetX(HFMath::lerp(velocity.GetX(), 0.0f, m_Deceleration * deltaTime));
    }
    else if (dirX)
    {
        // velocity.SetX(velocity.GetX() + dirX * m_Acceleration * deltaTime);
        velocity.SetX(HFMath::lerp(velocity.GetX(), dirX * m_MaxSpeed, m_Acceleration * deltaTime));
    }

    // if (velocity.GetX() > m_MaxSpeed)
    // {
    //     velocity.SetX(m_MaxSpeed);
    // }
    // else if (velocity.GetX() < -m_MaxSpeed)
    // {
    //     velocity.SetX(-m_MaxSpeed);
    // }
 
    velocity.SetY(velocity.GetY() + m_GRAVITY * deltaTime);

    HFMath::Vector2 xOffset = m_Transform.GetGlobalPosition() + HFMath::Vector2(velocity.GetX() * deltaTime, 0.0f);
    m_Transform.MoveAndCollide(xOffset);
    HFMath::Vector2 yOffset = m_Transform.GetGlobalPosition() + HFMath::Vector2(0.0f, velocity.GetY() * deltaTime);
    isOnFloor = m_Transform.MoveAndCollide(yOffset);
    // m_Transform.SetGlobalPosition( m_Transform.GetGlobalPosition() + HFMath::Vector2(xOffset.GetX(), yOffset.GetY()) );
    // m_Transform.SetGlobalPosition( m_Transform.GetGlobalPosition() + HFMath::Vector2(0.0f, 1.0f) );
    // std::cout << m_Transform.GetGlobalPosition() << "\n";

    if (isOnFloor)
    {
        velocity.SetY(0.0f);

        if(inputSystem.IsKeyJustDown(SDLK_SPACE))
        {
            velocity.SetY(-m_JumpForce);
        }
    }

    if (inputSystem.IsKeyJustDown(SDLK_LSHIFT))
    {
        velocity.SetX(dirX * m_DashForce);
    }
}

void Player::DirectionalMove(double deltaTime)
{
    float dirX = 0.0f;
    float dirY = 0.0f;

    HFInput& inputSystem = HFInput::GetInstance();

    if (inputSystem.IsKeyDown(SDLK_d))
    {
        dirX += 1.0f;
    }
    if (inputSystem.IsKeyDown(SDLK_a))
    {
        dirX -= 1.0f;
    }
    if(inputSystem.IsKeyDown(SDLK_w))
    {
        dirY -= 1.0f;
    }
    if(inputSystem.IsKeyDown(SDLK_s))
    {
        dirY += 1.0f;
    }

    HFMath::Vector2 dirVec = HFMath::Vector2(dirX, dirY);
    dirVec = dirVec.Normalized();
    
    velocity = dirVec * m_MaxSpeed * deltaTime;

    HFMath::Vector2 xOffset = m_Transform.GetGlobalPosition() + HFMath::Vector2(velocity.GetX(), 0.0f);
    m_Transform.MoveAndCollide(xOffset);
    HFMath::Vector2 yOffset = m_Transform.GetGlobalPosition() + HFMath::Vector2(0.0f, velocity.GetY());
    m_Transform.MoveAndCollide(yOffset);
}
