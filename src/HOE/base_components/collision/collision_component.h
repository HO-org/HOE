#pragma once
#include "world_component.h"
#include "hftransform.h"
#include "color_rect.h"
#include "misc.h"
#include "hfmath.h"


struct CollidingSides
{
    int numSides = 0;
    bool SIDE_TOP = false;
    bool SIDE_RIGHT = false;
    bool SIDE_BOTTOM = false;
    bool SIDE_LEFT = false;
};

// Currently only rectangle collisions are available
class CollisionComponent : public WorldComponent
{
    public:
        CollisionComponent()
        {
            m_Transform = HFTransform(); m_Size = HFMath::Vector2::ZERO();
            m_Name = "CollisionComponent";
        }
        CollisionComponent(HFMath::Vector2 position, HFMath::Vector2 size)
        {
            m_Transform.SetGlobalPosition(position); m_Size = size;
            m_Name = "CollisionComponent";
        }
        CollisionComponent(std::string name)
        {
            m_Transform = HFTransform();
            m_Size = HFMath::Vector2::ZERO();
            m_Name = name;
        }
        CollisionComponent(HFMath::Vector2 position, HFMath::Vector2 size, std::string name)
        {
            m_Transform.SetGlobalPosition(position);
            m_Size = size;
            m_Name = name;
        }

        void Init() override;

        std::vector<CollisionComponent*> GetOverlappingComponents();
        bool IsOverlapping(CollisionComponent* other);

        HFTransform m_Transform;
        HFMath::Vector2 m_Size = HFMath::Vector2::ZERO();

        void GetPoints(HFMath::Vector2* out_Points);

        CollidingSides GetCollidingSides(CollisionComponent* other);

        HFMath::Vector2 GetCollisionNormal(HFMath::Vector2 from);

        bool m_ShowVisual = false;
        ColorRect m_Visualizer;

private:
};