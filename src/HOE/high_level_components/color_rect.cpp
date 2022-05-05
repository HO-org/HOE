#include "color_rect.h"


void ColorRect::Draw(SDL_Renderer** renderer, Camera* mainCamera)
{
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();

    if (mainCamera != NULL)
    {
        pos = pos - mainCamera->m_Transform.GetGlobalPosition();
    }

    SDL_Rect rect = { (int)pos.GetX(), (int)pos.GetY(), (int)m_Size.GetX(), (int)m_Size.GetY() };
    SDL_SetRenderDrawColor(*renderer,  m_Color.r, m_Color.g, m_Color.b, m_Color.a);
    SDL_RenderFillRect(*renderer, &rect);
}
