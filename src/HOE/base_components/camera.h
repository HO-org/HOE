#pragma once
#include "world_component.h"
// #include "game.h"

class Game;

class Camera : public WorldComponent
{
public:
    void SetCenter(HFMath::Vector2 targetPos);
};