#pragma once
#include "world_component.h"
#include "hfmath.h"
#include "camera.h"
#include "SDL.h"


class RenderComponent : public WorldComponent
{
    public:
        RenderComponent() {}

        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        virtual void Draw(SDL_Renderer** renderer, Camera* mainCamera) {}

        virtual ~RenderComponent() {}
};