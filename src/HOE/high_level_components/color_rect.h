#pragma once
#include "render_component.h"
#include "misc.h"
#include "hftransform.h"
#include <string>

class ColorRect : public RenderComponent
{
public:
    ColorRect()
    {
        m_Transform.SetGlobalPosition(HFMath::Vector2::ZERO());
        m_Name = "ColorRect";
        m_Transform.m_Name = "ColorRectTransform";
    }
    ColorRect(HFMath::Vector2 position, HFMath::Vector2 size, std::string name)
    {
        m_Transform.SetGlobalPosition(position);
        m_Size = size;
        m_Name = name;
        m_Transform.m_Name = "ColorRectTransform";
    }
    ColorRect(HFMath::Vector2 position, HFMath::Vector2 size, std::string name, HFColor color)
    {
        m_Transform.SetGlobalPosition(position);
        m_Size = size;
        m_Color = color;
        m_Name = name;
        m_Transform.m_Name = "ColorRectTransform";
    }

    void Draw(SDL_Renderer** renderer, Camera* mainCamera) override;

    HFTransform m_Transform = HFTransform();
    HFMath::Vector2 m_Size = HFMath::Vector2(32.f, 32.f);

    HFColor m_Color = { 255, 255, 255, 255 };
};