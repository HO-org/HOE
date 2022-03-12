#pragma once
#include "raylib.h"
#include "hfmath.h"
#include "sprite.h"
#include "hftransform.h"
#include "world_component.h"

class Player : public WorldComponent
{
    public:
        Player() {}

        Player(float Pos_X, float Pos_Y)
        {
            // m_Position.SetX(Pos_X);
            // m_Position.SetY(Pos_Y);
            m_Transform.SetGlobalPosition(HFMath::Vector2(Pos_X, Pos_Y));
        }

        Player(HFMath::Vector2 initialPos) { 
            // m_Position.SetX(initialPos.GetX());
            // m_Position.SetY(initialPos.GetY());
            m_Transform.SetGlobalPosition(initialPos);
        }

        virtual void Update(double deltaTime) override;
        virtual void Ready() override;

        // HFMath::Vector2 GetPosition() { return m_Position; }
        
        Sprite m_Sprite;
        // Texture2D getTexture() { return m_Texture; }

    private:
        // HFMath::Vector2 m_Position;

        // Texture2D m_Texture;

        void Move(double deltaTime);
};