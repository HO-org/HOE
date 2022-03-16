#include "block.h"
#include "hflog.h"


void Block::Ready()
{
    m_Transform.AddChild(&m_Collision.m_Transform);
    m_Collision.m_Transform.SetGlobalPosition(m_Transform.GetGlobalPosition());
}

void Block::Draw()
{
    // HFLog::Log("Rendering block");
    DrawRectangle(m_Transform.GetGlobalPosition().GetX(), m_Transform.GetGlobalPosition().GetY(), m_Size.GetX(), m_Size.GetY(), m_Color);
}