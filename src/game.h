#pragma once
#include "component.h"
#include <vector>

class Game
{
    public:
        static Game& GetInstance() {
            static Game instance;

            return instance;
        }

        int getScreenWidth () { return m_ScreenWidth; }
        int getScreenHeight () { return m_ScreenHeight; }

        void initalize(int screenWidth, int screenHeight) { m_ScreenWidth = screenWidth; m_ScreenHeight = screenHeight; }

        std::vector<Component> m_Components;

        void ReadyComponents() { for (Component component: m_Components ) { component.Ready(); } }
        void UpdateComponents() { for ( Component component : m_Components ) { component.Update(deltaTime); } }

        double deltaTime;

    private:
        Game() {} ;

        int m_ScreenWidth;
        int m_ScreenHeight;
    
    public:
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
};