#include "hftransform.h"
#include "hfmath.h"
#include <iostream>
// #include <algorithm>

void HFTransform::UpdatePositionInChildren()
{
    for (HFTransform* child : m_Children)
    {
        child->UpdatePosition();
    }
}

void HFTransform::SetGlobalPosition(HFMath::Vector2 targetPos)
{
    m_GlobalPosition = targetPos;
    if (m_Parent)
    {
        m_LocalPosition = targetPos - m_Parent->GetGlobalPosition();
    } else { m_LocalPosition = HFMath::Vector2::ZERO(); }

    UpdatePositionInChildren();
}

void HFTransform::SetLocalPosition(HFMath::Vector2 targetPos)
{
    // if (m_Parent == NULL)
    // {
    //     m_LocalPosition = HFMath::Vector2::ZERO();
    //     std::cout << "Tried to set a local position on a component with no parent!" << std::endl;
    //     return;
    // }

    m_LocalPosition = targetPos;
    UpdatePosition();
    UpdatePositionInChildren();
}

void HFTransform::UpdatePosition()
{
    if (m_Parent == NULL)
    {
        return;
    }
    m_GlobalPosition = m_Parent->GetGlobalPosition() + m_LocalPosition;
}


void HFTransform::MoveTo(HFMath::Vector2 targetPos)
{
}


void HFTransform::SetParent(HFTransform* target)
{
    SetParentLink(target, this);
}

void HFTransform::AddChild(HFTransform* target)
{
    SetParentLink(this, target);
}


void HFTransform::SetParentLink(HFTransform* parent, HFTransform* child)
{
    if (std::find(parent->m_Children.begin(), parent->m_Children.end(), child) != parent->m_Children.end())
    { 
        return;
    }

    parent->m_Children.push_back(child);
    child->m_Parent = parent;

    child->UpdatePosition();
}


void HFTransform::AddCollider(CollisionComponent* collider)
{
    m_Colliders.push_back(collider);
}

void HFTransform::RemoveCollider(CollisionComponent* collider)
{
    std::remove_if(m_Colliders.begin(), m_Colliders.end(), [collider](CollisionComponent* c) { return c == collider; });
}