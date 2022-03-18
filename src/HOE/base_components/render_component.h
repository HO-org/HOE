#pragma once
#include "world_component.h"


class RenderComponent : public WorldComponent
{
    public:
        RenderComponent() {}

        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        virtual void Draw() {}

        virtual ~RenderComponent() {}
};