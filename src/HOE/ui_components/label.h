#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "sprite.h"


class Label : public Sprite
{
public:
    bool load(SDL_Renderer** renderer, std::string path) override;
    bool load(std::string path) override;

    void loadFont();
private:
    TTF_Font* m_Font;

    std::string m_Text;
    
    SDL_Color m_Color;
};