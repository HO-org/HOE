#pragma once
#include "render_component.h"
#include "collision_component.h"
#include "raylib.h"

class Block : public RenderComponent
{
    public:
        Block(HFMath::Vector2 size, HFMath::Vector2 position)
        {
            m_Size = size;
            m_Collision.m_Size = size;
            m_Transform.SetGlobalPosition(position);
        }
        Block(HFMath::Vector2 size)
        {
            m_Size = size;
            m_Collision.m_Size = size;
        }

        CollisionComponent m_Collision = CollisionComponent();
        
    private:
        virtual void Ready() override;
        virtual void Draw() override;

        Color m_Color = RED;

        HFTransform m_Transform;
        HFMath::Vector2 m_Size = HFMath::Vector2::ZERO();
};