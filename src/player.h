#pragma once
#include "raylib.h"
#include "hfmath.h"
#include "sprite.h"
#include "hftransform.h"
#include "world_component.h"
#include "collision_component.h"
#include "raycast.h"

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

        virtual ~Player() {}

        // HFMath::Vector2 GetPosition() { return m_Position; }
        
        Sprite m_Sprite;

        CollisionComponent m_Collider = CollisionComponent();
        // Texture2D getTexture() { return m_Texture; }

    private:
        // HFMath::Vector2 m_Position;

        // Texture2D m_Texture;
        bool isOnFloor = false;

        float speed = 130.0f;
        float jumpForce = 400.0f;
        float GRAVITY = 1000.0f;

        HFMath::Vector2 velocity;
        void Move(double deltaTime);
};