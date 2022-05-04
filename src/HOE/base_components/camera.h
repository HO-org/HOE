#pragma once
#include "world_component.h"
// #include "game.h"

class Game;

class Camera : public WorldComponent
{
public:
    Camera()
    {
        m_Name = "Camera";
    }

    void SetCenter(HFMath::Vector2 targetPos);

    float m_Zoom = 1.0f;
};