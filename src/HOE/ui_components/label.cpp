#include "label.h"
#include "game.h"
#include "hflog.h"


bool Label::refresh(SDL_Renderer** renderer)
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

    m_Texture = SDL_CreateTextureFromSurface(*renderer, textSurface);
    if (m_Texture == NULL)
    {
        logger.Log(HFLog::HF_ERROR, std::string("Unable to create texture from rendered text! SDL Error: ") + SDL_GetError(), __FILE__, __LINE__);
        
        SDL_FreeSurface( textSurface );
        return false;
    }
    
    m_Width = textSurface->w;
    m_Height = textSurface->h;

    SDL_FreeSurface( textSurface );

    return true;
}

bool Label::refresh()
{
    return refresh(Game::GetInstance().m_CurRenderer);
}


bool Label::loadFont(std::string path)
{
    HFLog& logger = HFLog::GetInstance();

    m_Font = TTF_OpenFont(path.c_str(), m_FontSize);
    if (m_Font == NULL)
    {
        logger.Log(HFLog::HF_ERROR, std::string("Failed to load font! SDL_ttf Error: ") + TTF_GetError(), __FILE__, __LINE__);
        return false;
    }

    return true;
}


void Label::setColor(HFColor color)
{
    m_Color = { color.r, color.g, color.b, color.a };
}


void Label::setText(std::string text)
{
    if (text == "")
    {
        m_Text = " ";
        return;
    }
    
    m_Text = text;
}