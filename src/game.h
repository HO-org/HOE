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

        std::vector<Component*> m_Components;
        std::vector<RenderComponent*> m_RenderComponents;

        void ReadyComponents() { for (Component* component : m_Components ) { component->Ready(); } }
        void UpdateComponents(double deltaTime) { for ( Component* component : m_Components ) { component->Update(deltaTime); } }
        void DrawComponents() { for (RenderComponent* component : m_RenderComponents) { component->Draw(); } }
        void AddComponent(Component* component) { m_Components.push_back(component); }
        void AddRenderComponents(RenderComponent* component) { m_RenderComponents.push_back(component); }

    private:
        Game() {} ;

        int m_ScreenWidth;
        int m_ScreenHeight;
    
    public:
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
};