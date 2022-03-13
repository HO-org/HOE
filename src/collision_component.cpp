#include "collision_component.h"
#include "game.h"


std::vector<CollisionComponent*> CollisionComponent::GetOverlappingComponents()
{
    Game& game = Game::GetInstance();

    std::vector<CollisionComponent*> collidingWith;

    for (CollisionComponent* collider : game.m_CollisionComponents)
    {   
        if (collider == this) { continue; }

        if (IsOverlapping(collider))
        {
            collidingWith.push_back(collider);
        }
    }

    return collidingWith;
}

bool CollisionComponent::IsOverlapping(CollisionComponent* other)
{
    float x = m_Transform.GetGlobalPosition().GetX();
    float otherX = other->m_Transform.GetGlobalPosition().GetX();
    
    float y = m_Transform.GetGlobalPosition().GetY();
    float otherY = other->m_Transform.GetGlobalPosition().GetY();
    
    float width = m_Size.GetX();
    float otherWidth = other->m_Size.GetX();

    float height = m_Size.GetY();
    float otherHeight = other->m_Size.GetY();

    return ( x + width >= otherX && x <= otherX + otherWidth )
           &&
           ( y + height >= otherY && y <= otherY + otherHeight );
}
