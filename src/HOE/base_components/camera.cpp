#include "camera.h"
#include "game.h"

void Camera::SetCenter(HFMath::Vector2 targetPos)
{
    HFMath::Vector2 gameResolution = HFMath::Vector2(Game::GetInstance().getScreenWidth(), Game::GetInstance().getScreenHeight());
    HFMath::Vector2 floored = HFMath::Vector2((int)targetPos.GetX(), (int)targetPos.GetY());
    m_Transform.SetGlobalPosition(floored - gameResolution / 2);
}