#pragma once
#include "component.h"
#include "hfmath.h"
#include <vector>

class CollisionComponent;
class Raycast;

class HFTransform : public Component
{
    public:
        HFTransform()
        {
            m_GlobalPosition = HFMath::Vector2::ZERO();
            m_LocalPosition = HFMath::Vector2::ZERO();
            m_Name = "Transform";
        }

        void SetGlobalPosition(HFMath::Vector2 targetPos);
        void SetLocalPosition(HFMath::Vector2 targetPos);
        HFMath::Vector2 GetGlobalPosition();
        HFMath::Vector2 GetLocalPosition();

        void SetScale(HFMath::Vector2 value);
        HFMath::Vector2 GetScale();

        void UpdatePosition();

        bool MoveAndCollide(HFMath::Vector2 targetPos);

        void SetParent(HFTransform* target);
        HFTransform* GetParent();

        void AddChild(HFTransform* target);
        std::vector<HFTransform*> GetChildren();

        void SetParentLink(HFTransform* parent, HFTransform* child);

        void AddCollider(CollisionComponent* collider);
        void RemoveCollider(CollisionComponent* collider);
        std::vector<CollisionComponent*> GetColliders();

        virtual ~HFTransform() {}

    private:
        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        HFMath::Vector2 m_LocalPosition;
        HFMath::Vector2 m_GlobalPosition;

        HFMath::Vector2 m_Scale = HFMath::Vector2(1.0f, 1.0f);

        HFTransform* m_Parent = nullptr;
        std::vector<HFTransform*> m_Children;

        std::vector<CollisionComponent*> m_Colliders;

        void UpdatePositionInChildren();
};
