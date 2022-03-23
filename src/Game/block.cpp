#include "block.h"
#include "hflog.h"
#include "game.h"

void Block::Init()
{
    Game& game = Game::GetInstance();

    game.AddComponentCallback(this, READY);
    game.AddRenderComponent(this);
    game.AddCollisionComponent(&m_Collision);
}

void Block::Ready()
{
    m_Transform.AddChild(&m_Collision.m_Transform);
    m_Collision.m_Transform.SetGlobalPosition(m_Transform.GetGlobalPosition());
}

void Block::Draw(SDL_Renderer** renderer)
{
    // HFLog::Log("Rendering block");
    // DrawRectangle(m_Transform.GetGlobalPosition().GetX(), m_Transform.GetGlobalPosition().GetY(), m_Size.GetX(), m_Size.GetY(), m_Color);
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();
    SDL_Rect drawRect = { (int)pos.GetX(), (int)pos.GetY(), (int)m_Size.GetX(), (int)m_Size.GetY() };
    SDL_SetRenderDrawColor(*renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
    SDL_RenderFillRect(*renderer, &drawRect);
}