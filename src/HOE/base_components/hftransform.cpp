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
    
    SetGlobalPosition(m_Parent->GetGlobalPosition() + m_LocalPosition);
}


void HFTransform::Move(HFMath::Vector2 amount)
{
    SetGlobalPosition(GetGlobalPosition() + amount);
}


bool HFTransform::MoveAndCollide(HFMath::Vector2 targetPos)
{
    for ( CollisionComponent* collider : m_Colliders )
    {
        HFMath::Vector2 startPos = collider->m_Transform.GetGlobalPosition();
        HFMath::Vector2 colOffset = GetGlobalPosition() - collider->m_Transform.GetGlobalPosition();

        SetGlobalPosition(targetPos);

        HFMath::Vector2 colTarPos = targetPos - colOffset;

        HFMath::Vector2 normal;

        float minDist = 0.0005f;

        std::vector<CollisionComponent*> overlaps = collider->GetOverlappingComponents();
        for ( CollisionComponent* overlap : overlaps )
        {
            HFMath::Vector2 center = startPos + collider->m_Size / 2;
            HFMath::Vector2 overlapCenter = overlap->m_Transform.GetGlobalPosition() + overlap->m_Size / 2;
            HFMath::Vector2 diff = center - overlapCenter;

            bool diffPointingRight = diff.GetX() > 0;
            bool diffPointingLeft = diff.GetX() < 0;
            bool isInHeight = abs(diff.GetY()) <= overlap->m_Size.GetY() / 2 + collider->m_Size.GetY() / 2;
            bool velocityGoingLeft = (colTarPos - startPos).GetX() < 0;
            bool velocityGoingRight = (colTarPos - startPos).GetX() > 0;

            bool diffPointingUp = diff.GetY() < 0;
            bool diffPointingDown = diff.GetY() > 0;
            bool isInWidth = abs(diff.GetX()) <= overlap->m_Size.GetX() / 2 + collider->m_Size.GetX() / 2;
            bool velocityGoingDown = (colTarPos - startPos).GetY() > 0;
            bool velocityGoingUp = (colTarPos - startPos).GetY() < 0;

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

                float tolerance = 0.00005f * std::max(collider->m_Size.GetX(), collider->m_Size.GetY());

                if (HFMath::fdist(normal.GetX(), 0.f) >= minDist);
                {
                    newPos.SetX(overlapCenter.GetX() + normal.GetX() * (overlap->m_Size.GetX() / 2 + collider->m_Size.GetX() / 2 + tolerance));
                    newPos.SetY(center.GetY());
                }
                if (HFMath::fdist(normal.GetY(), 0.f) >= minDist)
                {
                    newPos.SetY(overlapCenter.GetY() + normal.GetY() * (overlap->m_Size.GetY() / 2 + collider->m_Size.GetY() / 2 + tolerance));
                    newPos.SetX(center.GetX());
                }

                if (HFMath::fdist(newPos.GetX(), 0.f) >= minDist || HFMath::fdist(newPos.GetY(), 0.f) >= minDist)
                {
                    SetGlobalPosition((newPos - collider->m_Size / 2) + colOffset);
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
