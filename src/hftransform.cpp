#include "hftransform.h"
#include "hfmath.h"
#include <iostream>
#include "collision_component.h"
#include "hflog.h"
#include "raycast.h"
#include "game.h"
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


void HFTransform::MoveAndCollide(HFMath::Vector2 targetPos)
{
    bool hit = false;

    // Raycast ray = Raycast();
    // RaycastHitResult result = ray.CollideRay(targetPos);

    // CollisionComponent* overlap = 

    // HFMath::Vector2 tolerance = HFMath::Vector2(0.0005f, 0.0005f);

    // HFMath::Vector2 normal = overlap->GetCollisionNormal(GetGlobalPosition());

    // HFMath::Vector2 offset = (normal * -1 * collider->m_Size);

    // SetGlobalPosition(overlap->m_Transform.GetLocalPosition() + offset);

    // hit = true;

    if (!hit)
    {
        SetGlobalPosition(targetPos);
    }


    // RaycastHitResult result = Raycast::RayCastRay(m_Colliders[0], GetGlobalPosition(), targetPos);
    
    // if (result.hit)
    // {
    //     HFMath::Vector2 tolerance = HFMath::Vector2(0.5f, 0.5f);
    //     HFMath::Vector2 offset = HFMath::Vector2(
    //         result.position.directionTo(GetGlobalPosition()) * tolerance
    //     );

    //     SetGlobalPosition(result.position + offset);
    //     std::cout << "Target is: " << targetPos << std::endl;
    //     std::cout << "Moved to: " << result.position + offset << std::endl;
    // }
    // else
    // {
    //     SetGlobalPosition(targetPos);
    // }

    // bool hit = false;

    // for (CollisionComponent* collider : m_Colliders)
    // {
    //     std::vector<CollisionComponent*> overlaps = collider->GetOverlappingComponents();

    //     for (CollisionComponent* overlap : overlaps)
    //     {
    //         // Will only run if the overlaps list isn't empy, meaning we're colliding

    //         HFMath::Vector2 pos = collider->m_Transform.GetGlobalPosition();
    //         HFMath::Vector2 otherPos = overlap->m_Transform.GetGlobalPosition();

    //         HFMath::Vector2 tolerance = HFMath::Vector2(0.0005f, 0.0005f);



    //         // CollidingSides collidingSides = collider->GetCollidingSides(overlap);

    //         // if (collidingSides.SIDE_RIGHT)
    //         // {
    //         //     HFMath::Vector2 offset = HFMath::Vector2(
    //         //         -tolerance.GetX() - collider->m_Size.GetX(),
    //         //         pos.GetY() - otherPos.GetY()
    //         //     );
    //         //     SetGlobalPosition(otherPos + offset);
    //         //     hit = true;
    //         // }
    //         // else if (collidingSides.SIDE_TOP)
    //         // {
    //         //     HFMath::Vector2 offset = HFMath::Vector2(
    //         //         pos.GetX() - otherPos.GetX(),
    //         //         tolerance.GetY() + overlap->m_Size.GetY()
    //         //     );
    //         //     SetGlobalPosition(otherPos + offset);
    //         //     hit = true;
    //         // }
    //     }
    // }

    // if (!hit) { SetGlobalPosition(targetPos); }
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