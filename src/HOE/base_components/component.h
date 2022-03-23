#pragma once
#include "enums.h"

class Component
{
    friend class Game;
    public:
        Component() {}

        virtual void Init() {}
        virtual void Update(double deltaTime) {}
        virtual void PhysicsUpdate(double deltaTime) {}
        virtual void Ready() {}

        virtual ~Component() {}

        CallbackType registeredWhere = NOCALLBACK;
};