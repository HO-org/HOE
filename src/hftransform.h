#pragma once
#include "component.h"
#include "hfmath.h"
#include <vector>

class HFTransform : public Component
{
    public:
        HFTransform() {}

        void SetGlobalPosition(HFMath::Vector2 targetPos);
        void SetLocalPosition(HFMath::Vector2 targetPos);
        HFMath::Vector2 GetGlobalPosition() { return m_GlobalPosition; }
        HFMath::Vector2 GetLocalPosition() { return m_LocalPosition; }

        void UpdatePosition();

        void SetParent(HFTransform* target);
        HFTransform* GetParent() { return m_Parent; }

        void AddChild(HFTransform* target);
        std::vector<HFTransform*> GetChildren() { return m_Children; }

        void SetParentLink(HFTransform* parent, HFTransform* child);

    private:
        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        HFMath::Vector2 m_LocalPosition;
        HFMath::Vector2 m_GlobalPosition;

        HFTransform* m_Parent;
        std::vector<HFTransform*> m_Children;

        void UpdatePositionInChildren();
};