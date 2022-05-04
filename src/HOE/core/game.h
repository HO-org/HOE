#pragma once
#include "enums.h"
#include "render_component.h"
#include "collision_component.h"
#include "SDL.h"
#include "camera.h"
#include <vector>

// Singleton class
class Game
{
public:
    static Game& GetInstance() {
        static Game instance;

        return instance;
    }

    int getScreenWidth();
    int getScreenHeight();

    void initalize(int screenWidth, int screenHeight);

    std::vector<Component*> m_ReadyComponents;
    std::vector<Component*> m_UpdateComponents;
    std::vector<RenderComponent*> m_RenderComponents;
    std::vector<CollisionComponent*> m_CollisionComponents;

    std::vector<Component*> GetComponents();
    void AddComponent(Component* component);
    void AddRenderComponent(RenderComponent* component);
    void AddCollisionComponent(CollisionComponent* component);
    void AddComponentCallback(Component* component, CallbackType type);
    void RemoveComponent(Component* component, CallbackType type);
    void RemoveRenderComponent(Component* component);
    void RemoveCollisionComponent(Component* component);

    void InitComponents();
    void ReadyComponents();
    void UpdateComponents(double deltaTime);
    void PhysicsUpdateComponents(double deltaTime);
    void DrawComponents(SDL_Renderer** renderer, bool shouldZoom);

    SDL_Renderer** m_CurRenderer = NULL;

    Camera m_DefaultCamera = Camera();
    Camera* m_MainCamera = &m_DefaultCamera;

    const char* RENDER_SCALE_MODE = "1";

private:
    Game() {} ;

    bool ComponentInVector(Component* component, std::vector<Component*> vector);

    void SetCompID(Component* component);
    std::string GetCompIdentity(Component* component);
    bool ValidateCompIdentity(Component* component);

    int m_ScreenWidth;
    int m_ScreenHeight;

    std::vector<Component*> m_Components;

    int idCount = 0;

public:
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
};