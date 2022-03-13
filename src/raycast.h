#pragma once
#include "hfmath.h"

class CollisionComponent;


struct RaycastHitResult
{
    HFMath::Vector2 position;
    CollisionComponent* collider = nullptr;
};


CollisionComponent* RaycastPoint(HFMath::Vector2 pos);
