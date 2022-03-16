#pragma once
#include "hfmath.h"
#include "hftransform.h"

class CollisionComponent;


struct IntersectResult
{
    bool hit = false;
    HFMath::Vector2 position;
};

struct RaycastHitResult
{
    bool hit = false;
    HFMath::Vector2 position;
    CollisionComponent* collider = nullptr;
};


class Raycast
{
    public:
        Raycast()
        {
            m_Transform = HFTransform();
            m_Direction = HFMath::Vector2::ZERO();
        }

        void LookAt(HFMath::Vector2 target);

        HFTransform m_Transform;
        HFMath::Vector2 m_Direction;

        CollisionComponent* CastPoint(HFMath::Vector2 pos);

        RaycastHitResult CollideRay(CollisionComponent* origin, HFMath::Vector2 targetPos);

        IntersectResult IntersectRay(HFMath::Vector2 p1, HFMath::Vector2 p2);
};