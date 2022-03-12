#pragma once
#include "render_object.h"
#include "raylib.h"
#include "hfmath.h"
#include "hftransform.h"

class RenderObject;

class Sprite : public RenderObject
{
    public:
        Sprite() {}
        Sprite(const char* defaultPath) { m_DefaultPath = defaultPath; }

        virtual void Draw() override;
        virtual void Update(double deltaTime);
        virtual void Ready() override;

        void Load(const char* path);

        Texture2D GetTexture() { return m_Texture; }

        const char* m_DefaultPath;
        // HFMath::Vector2 m_Position = HFMath::Vector2::ZERO();

    private:
        Texture2D m_Texture;
        bool initialized = false;
};