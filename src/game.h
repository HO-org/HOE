#pragma once
// #include "component.h"
#include "enums.h"
#include "render_component.h"
#include "collision_component.h"
#include <vector>

class Component;

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

        std::vector<Component*> m_ReadyComponents;
        std::vector<Component*> m_UpdateComponents;
        std::vector<RenderComponent*> m_RenderComponents;
        std::vector<CollisionComponent*> m_CollisionComponents;

        void AddRenderComponent(RenderComponent* component);
        void AddCollisionComponent(CollisionComponent* component);
        void AddComponent(Component* component, CallbackType type);
        void RemoveComponent(Component* component, CallbackType type);
        void RemoveRenderComponent(Component* component);
        void RemoveCollisionComponent(Component* component);
       
        void ReadyComponents() { for (Component* component : m_ReadyComponents ) { component->Ready(); } }
        void UpdateComponents(double deltaTime) { for ( Component* component : m_UpdateComponents ) { component->Update(deltaTime); } }
        void DrawComponents() { for (RenderComponent* component : m_RenderComponents) { component->Draw(); } }

    private:
        Game() {} ;

        bool ComponentInVector(Component* component, std::vector<Component*> vector);

        int m_ScreenWidth;
        int m_ScreenHeight;

    public:
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
};