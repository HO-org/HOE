#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "sprite.h"
#include "misc.h"

class Label : public Sprite
{
public:
    Label()
    {
        m_Text = "EMPTY TEXT";
        setColor({255, 255, 255, 255});
        // m_Color = {255, 0, 0, 255};
        m_Name = "Label";
    }
    Label(std::string text, HFColor color, std::string name)
    {
        m_Text = text;
        setColor(color);
        // m_Color = {255, 0, 0, 255};
        m_Name = name;
    }

    bool refresh();

    bool load(SDL_Renderer** renderer, std::string path) override;
    bool load(std::string path) override;

    void setColor(HFColor color);
    void setText(std::string text);

    int m_FontSize = 28;
private:
    TTF_Font* m_Font;

    std::string m_Text;
    
    SDL_Color m_Color;

    std::string m_PathCache;
};