#pragma once
#include "raylib.h"

class Player
{
    public:
        Player() {}

        Player(float Pos_X, float Pos_Y)
        {
            m_PosX = Pos_X;
            m_PosY = Pos_Y;
        }

        void Update(double deltaTime);
        void Ready(int screenWidth, int screenHeight);

        float getPosX() { return m_PosX; }
        float getPosY() { return m_PosY; }
        
        Texture2D getTexture() { return m_Texture; }

    private:
        float m_PosX;
        float m_PosY;

        Texture2D m_Texture;
};