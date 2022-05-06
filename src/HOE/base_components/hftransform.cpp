#include "hftransform.h"
#include "hfmath.h"
#include <iostream>
#include "collision_component.h"
#include "raycast.h"
#include "game.h"
#include <math.h>
#include <algorithm>

// #include <algorithm>


HFMath::Vector2 HFTransform::GetGlobalPosition()
{
    return m_GlobalPosition;
}

HFMath::Vector2 HFTransform::GetLocalPosition()
{
    return m_LocalPosition;
}


HFMath::Vector2 HFTransform::GetScale()
{
    return m_Scale;
}


HFTransform* HFTransform::GetParent()
{
    return m_Parent;
}


std::vector<HFTransform*> HFTransform::GetChildren()
{
    return m_Children;
}


std::vector<CollisionComponent*> HFTransform::GetColliders()
{
    return m_Colliders;
}


void HFTransform::UpdatePositionInChildren()
{
    for (HFTransform* child : m_Children)
    {
        child->UpdatePosition();
    }
}


void HFTransform::SetScale(HFMath::Vector2 value)
{
    m_Scale = value;
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


void HFTransform::Move(HFMath::Vector2 amount)
{
    SetGlobalPosition(GetGlobalPosition() + amount);
}


bool HFTransform::MoveAndCollide(HFMath::Vector2 targetPos)
{
    HFMath::Vector2 originalPos = GetGlobalPosition();

    SetGlobalPosition(targetPos);

    HFMath::Vector2 normal;

    for ( CollisionComponent* collider : m_Colliders )
    {
        std::vector<CollisionComponent*> overlaps = collider->GetOverlappingComponents();
        for ( CollisionComponent* overlap : overlaps )
        {
            HFMath::Vector2 center = originalPos + collider->m_Size / 2;
            HFMath::Vector2 overlapCenter = overlap->m_Transform.GetGlobalPosition() + overlap->m_Size / 2;
            HFMath::Vector2 diff = center - overlapCenter;

            bool diffPointingRight = diff.GetX() > 0;
            bool diffPointingLeft = diff.GetX() < 0;
            bool isInHeight = abs(diff.GetY()) <= overlap->m_Size.GetY() / 2 + collider->m_Size.GetY() / 2;
            bool velocityGoingLeft = (targetPos - originalPos).GetX() < 0;
            bool velocityGoingRight = (targetPos - originalPos).GetX() > 0;

            bool diffPointingUp = diff.GetY() < 0;
            bool diffPointingDown = diff.GetY() > 0;
            bool isInWidth = abs(diff.GetX()) <= overlap->m_Size.GetX() / 2 + collider->m_Size.GetX() / 2;
            bool velocityGoingDown = (targetPos - originalPos).GetY() > 0;
            bool velocityGoingUp = (targetPos - originalPos).GetY() < 0;

            if (diffPointingRight
            && isInHeight
            && velocityGoingLeft)
            {
                normal = HFMath::Vector2(1.0f, 0.0f);
            }
            if (diffPointingLeft
            && isInHeight
            && velocityGoingRight)
            {
                normal = HFMath::Vector2(-1.0f, 0.0f);
            }
            if (diffPointingUp
            && isInWidth
            && velocityGoingDown)
            {
                normal = HFMath::Vector2(0.0f, -1.0f);
            }
            if (diffPointingDown
            && isInWidth
            && velocityGoingUp)
            {
                normal = HFMath::Vector2(0.0f, 1.0f);
            }

            if (normal.Length())
            {
                HFMath::Vector2 newPos = center;

                float tolerance = 0.00001f * std::max(collider->m_Size.GetX(), collider->m_Size.GetY());

                if (normal.GetX() != 0.0f)
                {
                    newPos.SetX(overlapCenter.GetX() + normal.GetX() * (overlap->m_Size.GetX() / 2 + collider->m_Size.GetX() / 2 + tolerance));
                    newPos.SetY(center.GetY());
                }
                if (normal.GetY() != 0.0f)
                {
                    newPos.SetX(center.GetX());
                    newPos.SetY(overlapCenter.GetY() + normal.GetY() * (overlap->m_Size.GetY() / 2 + collider->m_Size.GetY() / 2 + tolerance));
                }

                if (newPos.GetX() != 0.0f || newPos.GetY() != 0.0f)
                {
                    SetGlobalPosition(newPos - collider->m_Size / 2);
                }
            }
            // If we have a collision 
            return true;
        }
    }

    return false;
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
