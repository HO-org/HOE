#include "sprite.h"
#include "raylib.h"



void Sprite::Ready()
{
    if (!initialized && !m_DefaultPath)
    {
        Load(m_DefaultPath);
    }
}

void Sprite::Update(double deltaTime)
{
    
}


void Sprite::Load(const char* path)
{
    m_Texture = LoadTexture(path);
    initialized = true;
}


void Sprite::Draw()
{
    if (!initialized) {
        std::cout << "Trying to draw uninitialized sprite!" << std::endl;
        return;
    }

    DrawTexture(m_Texture, m_Transform.GetGlobalPosition().GetX(), m_Transform.GetGlobalPosition().GetY(), WHITE);
}