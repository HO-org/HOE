#include "block.h"
#include "game.h"


HFMath::Vector2 Block::GetSize()
{
    return m_Size;
}


void Block::Init()
{
    Game& game = Game::GetInstance();

    game.AddComponentCallback(this, READY);
    // game.AddRenderComponent(this);
    game.AddCollisionComponent(&m_Collision);
}

void Block::Ready()
{
    m_Transform.AddChild(&m_Collision.m_Transform);
    m_Collision.m_Transform.SetGlobalPosition(m_Transform.GetGlobalPosition());
}

void Block::Draw(SDL_Renderer** renderer, Camera* mainCamera)
{
    // DrawRectangle(m_Transform.GetGlobalPosition().GetX(), m_Transform.GetGlobalPosition().GetY(), m_Size.GetX(), m_Size.GetY(), m_Color);
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();
    if (mainCamera != NULL)
    {
        pos = pos - mainCamera->m_Transform.GetGlobalPosition();
    }
    SDL_Rect drawRect = { (int)pos.GetX(), (int)pos.GetY(), (int)m_Size.GetX(), (int)m_Size.GetY() };
    SDL_SetRenderDrawColor(*renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
    SDL_RenderFillRect(*renderer, &drawRect);
}