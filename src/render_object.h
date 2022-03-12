#pragma once
#include "world_component.h"


class RenderObject : public WorldComponent
{
    public:
        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        virtual void Draw();
};