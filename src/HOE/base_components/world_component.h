#pragma once
#include "component.h"
#include "hftransform.h"

class WorldComponent : public Component
{   
    public:
        WorldComponent() {}

        virtual void Update(double deltaTime) {}
        virtual void Ready() {}

        virtual ~WorldComponent() {}

        HFTransform m_Transform;
};