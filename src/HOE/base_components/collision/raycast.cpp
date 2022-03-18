#include "raycast.h"
#include "game.h"
#include "collision_component.h"

CollisionComponent* Raycast::CastPoint(HFMath::Vector2 pos)
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
    }

    return nullptr;
}

// RaycastHitResult Raycast::RayCastRay(CollisionComponent* origin, HFMath::Vector2 startPos, HFMath::Vector2 targetPos)
// {
//     Game& game = Game::GetInstance();

//     HFMath::Vector2 finalPoint = HFMath::Vector2();

//     RaycastHitResult result;
//     result.hit = false; 

//     for ( CollisionComponent* collider : game.m_CollisionComponents )
//     {
//         if (collider == origin) { continue; }

//         HFMath::Vector2 points[4];
//         collider->GetPoints(points);

//         HFMath::Vector2 closestPoint;

//         // For each edge
//         for (int i = 0; i < 4; i++)
//         {
//             // Loop to the first point if on the last
//             int nextPoint = i + 1;
//             if (i == 3) { nextPoint = 0; }

//             // Get the intersection point of the raycast with the edge
//             HFMath::Vector2 hitPoint = HFMath::lineIntersection(startPos, targetPos, points[i], points[nextPoint]);

//             // If the line is too long, skip and check against the next edge
//             float hitLength = (hitPoint - startPos).Length();
//             float originalLength = (targetPos - startPos).Length();
//             if (hitLength > originalLength) { continue; }
            

//             // If the lenght is shorter than last time, the line is closer, so we override it and report a hit
//             if (result.hit == false || hitLength < (closestPoint).Length())
//             {
//                 closestPoint = hitPoint;
//                 result.hit = true;
//             }
//         }

//         bool firstTime = true;
//         // if the closest point of the collider is closer to the start position than the previous collider's, set it to the finalPoint variable
//         if (firstTime || (closestPoint - targetPos).Length() < (finalPoint - targetPos).Length())
//         {
//             finalPoint = closestPoint;
//         }
//     }

//     result.position = finalPoint;

//     return result;
// }


void Raycast::LookAt(HFMath::Vector2 target)
{
    m_Direction = target - m_Direction;
    m_Direction = m_Direction.Normalized();
}



IntersectResult Raycast::IntersectRay(HFMath::Vector2 p1, HFMath::Vector2 p2)
{
    IntersectResult result;

    HFMath::Vector2 p3 = m_Transform.GetGlobalPosition();
    HFMath::Vector2 p4 = m_Transform.GetGlobalPosition() + m_Direction;

    const double den = (p1.GetX() - p2.GetX()) * (p3.GetY() - p4.GetY()) - (p1.GetY() - p2.GetY()) * (p3.GetX() - p4.GetX());
    if (den == 0)
    {
        result.hit = false;
        result.position = HFMath::Vector2::ZERO();
        return result;
    }

    const double t = ( (p1.GetX() - p3.GetX()) * (p3.GetY() - p4.GetY()) - (p1.GetY() - p3.GetY()) * (p3.GetX() - p4.GetX()) ) / den;

    const double u = -( (p1.GetX() - p2.GetX()) * (p1.GetY() - p3.GetY()) - (p1.GetY() - p2.GetY()) * (p1.GetX() - p3.GetX()) ) / den;

    if (t > 0 && t < 1 && u > 0)
    {
        result.hit = true;
        result.position.SetX( p1.GetX() + t * (p2.GetX() - p1.GetX()) );
        result.position.SetY( p1.GetY() + t * (p2.GetY() - p1.GetY()) );
    }
    else
    {
        result.hit = false;
    }

    return result;
}


RaycastHitResult Raycast::CollideRay(CollisionComponent* ignore, HFMath::Vector2 targetPos)
{
    RaycastHitResult result;
    HFMath::Vector2 closestPoint = HFMath::Vector2::ZERO();
    result.hit = false;

    Game& game = Game::GetInstance();

    LookAt(targetPos);

    HFMath::Vector2 startPos;

    float range = (targetPos - startPos).Length();

    bool hitPoint = false;

    for ( CollisionComponent* collider : game.m_CollisionComponents )
    {
        if (collider == ignore) { continue; }

        HFMath::Vector2 points[4];
        collider->GetPoints(points);

        HFMath::Vector2 closestEdgePoint = HFMath::Vector2::ZERO();
        bool hitEdge = false;

        for (int i = 0; i < 4; i++)
        {
            int nextPoint = i + 1;
            if (i == 3) { nextPoint = 0; }

            // std::cout << "Line: " << points[i] << ", " << points[nextPoint] << std::endl;

            IntersectResult intersectResult = IntersectRay(points[i], points[nextPoint]);

            if (!intersectResult.hit) { continue;  }

            std::cout << "Got here" << i << std::endl;

            float distance = (intersectResult.position - startPos).Length();
            if (distance > range) { continue; }

            if ( !hitEdge || (hitEdge && distance < (closestEdgePoint - startPos).Length()) )
            {
                closestEdgePoint = intersectResult.position;
                hitEdge = true;
            }
        }

        float distance = (closestEdgePoint - startPos).Length();

        // if ( !hitPoint ) { std::cout << "test" << std::endl; }

        if ( !hitPoint || (hitPoint && distance < (closestPoint - startPos).Length()) )
        {
            // std::cout << closestEdgePoint << std::endl;
            closestPoint = closestEdgePoint;
            result.collider = collider;
            hitPoint = true;
        }
    }

    if (hitPoint)
    {
        result.hit = true;
        result.position = closestPoint;
    }

    return result;
}
