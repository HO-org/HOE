#include "raycast.h"
#include "game.h"

CollisionComponent* RaycastPoint(HFMath::Vector2 pos)
{
    Game& game = Game::GetInstance();
    for ( CollisionComponent* collider : game.m_CollisionComponents )
    {
        float colliderX = collider->m_Transform.GetGlobalPosition().GetX();
        float colliderWidth = collider->m_Size.GetX();
        float colliderY = collider->m_Transform.GetGlobalPosition().GetY();
        float colliderHeight = collider->m_Size.GetY();

        if (
            (pos.GetX() >= colliderX && pos.GetX() <= colliderX + colliderWidth)
            &&
            (pos.GetY() >= colliderY && pos.GetY() <= colliderY + colliderHeight)
        )
        {
            return collider;
        }

        return nullptr;
    }
}