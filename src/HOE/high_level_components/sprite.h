#pragma once
#include "SDL.h"
#include "render_component.h"

class Sprite : public RenderComponent
{
public:
    Sprite()
    {
        m_Texture = NULL;
        m_Width = 0;
        m_Height = 0;

        m_Name = "Sprite";
    }

    ~Sprite()
    {
        freeResources();
    }

    bool load(SDL_Renderer** renderer, std::string path);
    bool load(std::string path);

    void freeResources();

    void Draw(SDL_Renderer** renderer, Camera* mainCamera) override;
    void DrawRepeat(SDL_Renderer** renderer, HFMath::Vector2 startPos);

    int getWidth();
    int getHeight();

    SDL_Texture* m_Texture;

    bool m_Repeat = false;
    bool m_OverrideSize = false;
    HFMath::Vector2 m_DrawSize = HFMath::Vector2(1.0f, 1.0f);

    HFMath::Vector2 m_Scale = HFMath::Vector2(1.0f, 1.0f);

private:
    int m_Width, m_Height;
};
