#pragma once
#include "component.h"
#include "hftransform.h"

class WorldComponent : public Component
{   
    public:
        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        HFTransform m_Transform;
};