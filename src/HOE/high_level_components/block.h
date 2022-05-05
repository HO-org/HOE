#pragma once
#include "render_component.h"
#include "collision_component.h"
#include "misc.h"
#include "SDL.h"
#include <string>

class Block : public RenderComponent
{
    public:
        Block(HFMath::Vector2 size, HFMath::Vector2 position)
        {
            m_Size = size;
            m_Collision.m_Size = size;
            m_Transform.SetGlobalPosition(position);
            m_Name = "Block";
        }
        Block(HFMath::Vector2 size)
        {
            m_Size = size;
            m_Collision.m_Size = size;
            m_Name = "Block";
        }
        Block(HFMath::Vector2 size, HFMath::Vector2 position, std::string name)
        {
            m_Size = size;
            m_Collision.m_Size = size;
            m_Transform.SetGlobalPosition(position);
            m_Name = name;
        }

        virtual ~Block() {}
        
        CollisionComponent m_Collision = CollisionComponent();

        HFMath::Vector2 GetSize();
        HFTransform m_Transform;

        HFColor m_Color = { 255, 0, 0, 255 };

    private:
        virtual void Init() override;
        virtual void Ready() override;
        virtual void Draw(SDL_Renderer** renderer, Camera* mainCamera) override;
        virtual void Update() {}


        HFMath::Vector2 m_Size = HFMath::Vector2::ZERO();
};