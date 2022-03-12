#pragma once


class Component
{
    friend class Game;
    public:
        virtual void Update(double deltaTime);
        virtual void Ready();
};