#include "collision_component.h"
#include "game.h"

void CollisionComponent::Init()
{
    Game& game = Game::GetInstance();

    #ifndef NDEBUG
    if (game.m_ForceCollisionVisuals || m_ShowVisual)
    {
        m_Visualizer = ColorRect(m_Transform.GetGlobalPosition(), m_Size, "CollisionVisualizer", { 0, 70, 255, 50 });
        m_Transform.AddChild(&m_Visualizer.m_Transform);
        game.AddRenderComponent(&m_Visualizer);
    }
    #endif
}


void CollisionComponent::SetSize(HFMath::Vector2 size)
{
    m_Size = size;
    m_Visualizer.m_Size = size;
}


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


HFMath::Vector2 CollisionComponent::GetCollisionNormal(HFMath::Vector2 from)
{
    HFMath::Vector2 center = m_Transform.GetGlobalPosition() + m_Size / 2;

    HFMath::Vector2 delta = center - from;

    float x, y;

    if (delta.GetX() >= 0.0f)
    {
        x = 1.0f;
    }
    else
    {
        x = -1.0f;
    }

    if (delta.GetY() >= 0.0f)
    {
        y = 1.0f;
    }
    else
    {
        y = -1.0f;
    }

    return HFMath::Vector2(x, y).Normalized();
}


void CollisionComponent::GetPoints(HFMath::Vector2* out_Points)
{
    HFMath::Vector2 pos = m_Transform.GetGlobalPosition();
    // Top left
    out_Points[0] = HFMath::Vector2(pos);
    // Top right
    out_Points[1] = HFMath::Vector2(pos + HFMath::Vector2(m_Size.GetX(), 0.0f));
    // Bottom right
    out_Points[2] = HFMath::Vector2(pos + m_Size);
    // Bottom left
    out_Points[3] = HFMath::Vector2(pos + HFMath::Vector2(0.0f, m_Size.GetY()));
}


CollidingSides CollisionComponent::GetCollidingSides(CollisionComponent* other)
{
    CollidingSides result;

    float width = m_Size.GetX();
    float otherWidth = other->m_Size.GetX();
    
    float left = m_Transform.GetGlobalPosition().GetX();
    float otherLeft = other->m_Transform.GetGlobalPosition().GetX();

    float right = left + width;
    float otherRight = otherLeft + otherWidth;

    float height = m_Size.GetY();
    float otherHeight = other->m_Size.GetY();
    
    float top = m_Transform.GetGlobalPosition().GetY();
    float otherTop = other->m_Transform.GetGlobalPosition().GetY();

    float bottom = top + height;
    float otherBottom = otherTop + otherHeight;

    if ( top >= otherTop && top <= otherBottom ) { result.SIDE_TOP = true; result.numSides++; }
    if ( right >= otherLeft && right <= otherRight ) { result.SIDE_RIGHT = true; result.numSides++; }
    if ( bottom >= otherTop && bottom <= otherBottom ) { result.SIDE_BOTTOM = true; result.numSides++; }
    if ( left >= otherLeft && left <= otherRight ) { result.SIDE_LEFT = true; result.numSides++; }

    return result;
}
