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

    void freeResources();

    void Draw(SDL_Renderer** renderer, Camera* mainCamera) override;

    int getWidth();
    int getHeight();

    SDL_Texture* m_Texture;

private:
    int m_Width, m_Height;
};
