#include "color_rect.h"
#include <math.h>


void ColorRect::Draw(SDL_Renderer** renderer, Camera* mainCamera)
{
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();

    if (mainCamera != NULL)
    {
        pos = pos - mainCamera->m_Transform.GetGlobalPosition();
    }

    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

    SDL_Rect rect = { (int)round(pos.GetX()), (int)round(pos.GetY()), (int)round(m_Size.GetX()), (int)round(m_Size.GetY()) };
    SDL_SetRenderDrawColor(*renderer,  m_Color.r, m_Color.g, m_Color.b, m_Color.a);
    SDL_RenderFillRect(*renderer, &rect);
}
