#pragma once
#include "world_component.h"
#include "hftransform.h"
#include "hfmath.h"

// Currently only rectangle collisions are available
class CollisionComponent : public WorldComponent
{
    public:
        CollisionComponent() { m_Transform = HFTransform(); m_Size = HFMath::Vector2::ZERO(); }
        CollisionComponent(HFMath::Vector2 position, HFMath::Vector2 size) { m_Transform.SetGlobalPosition(position); m_Size = size; }

        std::vector<CollisionComponent*> GetOverlappingComponents();
        bool IsOverlapping(CollisionComponent* other);

        HFTransform m_Transform;
        HFMath::Vector2 m_Size = HFMath::Vector2::ZERO();
};