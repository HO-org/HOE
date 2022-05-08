#include "label.h"
#include "game.h"
#include "hflog.h"


bool Label::load(SDL_Renderer** renderer, std::string path)
{
    HFLog& logger = HFLog::GetInstance();

    if (m_Texture != NULL)
    {
        freeResources();
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);
    if (textSurface == NULL)
    {
        logger.Log(HFLog::HF_ERROR, std::string("Unable to create render text surface! SDL_ttf Error: ") + TTF_GetError(), __FILE__, __LINE__);
        return false;
    }

    m_Width = textSurface->w;
    m_Height = textSurface->h;

    SDL_FreeSurface( textSurface );

    return true;
}

bool Label::load(std::string path)
{
    load(Game::GetInstance().m_CurRenderer, path);
}