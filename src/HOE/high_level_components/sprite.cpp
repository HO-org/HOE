#include "sprite.h"
#include "SDL_image.h"
#include "game.h"
#include "hfmath.h"
#include "hflog.h"


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

void Sprite::Draw(SDL_Renderer** renderer, Camera* mainCamera)
{
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();
    if (mainCamera != NULL)
    {
        pos = pos - mainCamera->m_Transform.GetGlobalPosition();
    }
    SDL_Rect renderRect = { (int)pos.GetX(), (int)pos.GetY(), m_Width, m_Height };
    SDL_RenderCopy(*renderer, m_Texture, NULL, &renderRect);
}

int Sprite::getHeight() { return m_Height; }
int Sprite::getWidth() { return m_Width; }
