#include "sprite.h"
#include "SDL_image.h"
#include "game.h"
#include "hfmath.h"
#include "hflog.h"
#include <math.h>


bool Sprite::load(SDL_Renderer** renderer, std::string path)
{
    const char* prevQuality = SDL_GetHint(SDL_HINT_RENDER_SCALE_QUALITY);
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
    {
        HFLog::GetInstance().Log(HFLog::HF_WARNING, std::string("Could not set render scale quality! SDL Error: ") + SDL_GetError(), __FILE__, __LINE__);
    }

    if(m_Texture != NULL)
    {
        freeResources();
    }

    SDL_Texture* texture = NULL;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        printf("Could not load image at %s. IMG_Load Error: %s\n", path.c_str(), IMG_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, prevQuality);
        return false;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));

    texture = SDL_CreateTextureFromSurface(*renderer, surface);
    if (texture == NULL)
    {
        printf("Could not create texture from %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, prevQuality);
        return false;
    }

    m_Width = surface->w;
    m_Height = surface->h;

    SDL_FreeSurface(surface);

    m_Texture = texture;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, prevQuality);

    return true;
}

void Sprite::freeResources()
{
    if (m_Texture == NULL)
    {
        return;
    }

    SDL_DestroyTexture(m_Texture);
    m_Texture = NULL;
    m_Width = 0;
    m_Height = 0;
}


void Sprite::DrawRepeat(SDL_Renderer** renderer, HFMath::Vector2 startPos)
{
    // int width = m_OverrideSize ? m_Width : lround(m_DrawSize.GetX());
    // int height = m_OverrideSize ? m_Height : lround(m_DrawSize.GetY());

    int widthSc = lround(m_Width * m_Scale.GetX());
    int heightSc = lround(m_Height * m_Scale.GetY());

    int drawWidth = 0;
    int drawHeight = 0;
    if (m_OverrideSize)
    {
        drawWidth = lround(m_DrawSize.GetX());
        drawHeight = lround(m_DrawSize.GetY());
    } else {
        drawWidth = widthSc;
        drawHeight = heightSc;
    }

    SDL_Rect rect = { lround(startPos.GetX()), lround(startPos.GetY()), widthSc, heightSc };
    
    int startX = rect.x;
    int startY = rect.y;

    int repeatW = drawWidth / widthSc;
    int repeatH = drawHeight / heightSc;

    for (int i = 0; i < repeatW; i++) {
        rect.x = startX + widthSc * i;
        SDL_RenderCopy(*renderer, m_Texture, NULL, &rect);

        for (int j = 0; j < repeatH; j++) {
            rect.y = startY + j * heightSc;
            SDL_RenderCopy(*renderer, m_Texture, NULL, &rect);
        }
    }
}


void Sprite::Draw(SDL_Renderer** renderer, Camera* mainCamera)
{
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();
    if (mainCamera != NULL)
    {
        pos = pos - mainCamera->m_Transform.GetGlobalPosition();
    }

    if (m_Repeat)
    {
        DrawRepeat(renderer, pos);
        return;
    }

    SDL_Rect renderRect = { lround(pos.GetX()), lround(pos.GetY()), lround(m_Width * m_Scale.GetX()), lround(m_Height * m_Scale.GetY()) };

    if (m_OverrideSize)
    {
        renderRect.w = lround(m_DrawSize.GetX());
        renderRect.h = lround(m_DrawSize.GetY());
    }

    SDL_RenderCopy(*renderer, m_Texture, NULL, &renderRect);
}

int Sprite::getHeight() { return m_Height; }
int Sprite::getWidth() { return m_Width; }
