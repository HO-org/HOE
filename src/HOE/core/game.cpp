#include "game.h"
#include <algorithm>
#include "hflog.h"


static HFLog& g_Logger = HFLog::GetInstance();


int Game::getScreenWidth()
{
    return m_ScreenWidth;
}


int Game::getScreenHeight()
{
    return m_ScreenHeight;
}


void Game::initalize(int screenWidth, int screenHeight)
{
    m_ScreenWidth = screenWidth;
    m_ScreenHeight = screenHeight;

    g_Logger.Log(HFLog::HF_INFO, "Game module initialized.", __FILE__, __LINE__);
}


std::vector<Component*> Game::GetComponents()
{
    return m_Components;
}

void Game::AddComponent(Component* component)
{
    m_Components.push_back(component);

    g_Logger.Log(HFLog::HF_FILE_ONLY, "Added component...", __FILE__, __LINE__);
}


void Game::InitComponents()
{
    for (Component* component : m_Components)
    {
        component->Init();
    }

    g_Logger.DLog(HFLog::HF_INFO, "Components Initialized!", __FILE__, __LINE__);
}


void Game::ReadyComponents()
{
    for (Component* component : m_ReadyComponents )
    {
        component->Ready();
    }

    g_Logger.DLog(HFLog::HF_INFO, "Components ready!", __FILE__, __LINE__);
}


void Game::UpdateComponents(double deltaTime)
{
    for ( Component* component : m_UpdateComponents )
    {
        component->Update(deltaTime);
    }
}


void Game::PhysicsUpdateComponents(double deltaTime)
{
    for ( Component* component : m_UpdateComponents )
    {
        component->PhysicsUpdate(deltaTime);
    }
}


void Game::DrawComponents(SDL_Renderer** renderer)
{
    for (RenderComponent* component : m_RenderComponents)
    {
        component->Draw(renderer, m_MainCamera);
    }
}


bool Game::ComponentInVector(Component* component, std::vector<Component*> v)
{
    if (
        std::find_if(v.begin(), v.end(), [component](Component* c) { return c == component; }) != v.end()
    ) { return true; }

    return false;
}


void Game::AddComponentCallback(Component* component, CallbackType type)
{
    switch (type)
    {
        case UPDATE:
            if (ComponentInVector(component, m_UpdateComponents)) 
            { 
                printf("Component already registered as an update component!");
                break;
            }


            m_UpdateComponents.push_back(component);
            component->registeredWhere = UPDATE;
            break;

        case READY:
            if (ComponentInVector(component, m_ReadyComponents)) 
            { 
                printf("Component already registered as a ready component!");
                break;
            }

            m_ReadyComponents.push_back(component);
            component->registeredWhere = READY;
            break;

        case READYUPDATE:
            if (ComponentInVector(component, m_UpdateComponents) || ComponentInVector(component, m_ReadyComponents)) 
            { 
                printf("Component already registered as an update/ready component!");
                break;
            }

            m_ReadyComponents.push_back(component);
            m_UpdateComponents.push_back(component);
            component->registeredWhere = READYUPDATE;
            break;

        default:
            printf("Tried to add a component with an invalid type passed");
            break;
    }
}


void Game::AddRenderComponent(RenderComponent* component)
{
    // if ( std::find(m_RenderComponents.begin(), m_RenderComponents.end(), component) != m_RenderComponents.end() )
    if (
        std::find_if(m_RenderComponents.begin(), m_RenderComponents.end(), [component](RenderComponent* c) { return c == component; }) != m_RenderComponents.end()
    )
    {
        g_Logger.Log(HFLog::HF_WARNING, "Tried to add render component that is already registered!", __FILE__, __LINE__);
        return;
    }

    m_RenderComponents.push_back(component);

    switch (component->registeredWhere)
    {
        case READY:
            component->registeredWhere = READYRENDER;
            break;
        
        case UPDATE:
            component->registeredWhere = UPDATERENDER;
            break;

        case READYUPDATE:
            component->registeredWhere = READYUPDATERENDER;
            break;
        
        case NOCALLBACK:
            component->registeredWhere = COLLISION;
            break;
        
        default:
            break;
    }

    g_Logger.Log(HFLog::HF_FILE_ONLY, "Added render component.", __FILE__, __LINE__);
}

void Game::AddCollisionComponent(CollisionComponent* component)
{
    // if ( std::find(m_CollisionComponents.begin(), m_CollisionComponents.end(), component) != m_CollisionComponents.end() )
    if (
        std::find_if(m_CollisionComponents.begin(), m_CollisionComponents.end(), [component](CollisionComponent* c) { return c == component; }) != m_CollisionComponents.end()
    )
    {
        g_Logger.Log(HFLog::HF_WARNING, "Tried to add collision component that is already registered!", __FILE__, __LINE__);
        return;
    }

    m_CollisionComponents.push_back(component);

    switch (component->registeredWhere)
    {
        case READY:
            component->registeredWhere = READYCOLLISION;
            break;
        
        case UPDATE:
            component->registeredWhere = UPDATECOLLISION;
            break;

        case READYUPDATE:
            component->registeredWhere = READYUPDATECOLLISION;
            break;
        
        case NOCALLBACK:
            component->registeredWhere = COLLISION;
            break;
        
        default:
            break;
    }

    g_Logger.Log(HFLog::HF_FILE_ONLY, "Added collision component.", __FILE__, __LINE__);
}


void Game::RemoveComponent(Component* component, CallbackType type)
{
    g_Logger.Log(HFLog::HF_ERROR, "CURRENTLY REMOVING COMPONENTS IS NOT IMPLEMENTED", __FILE__, __LINE__);
}

void Game::RemoveRenderComponent(Component* component) { g_Logger.Log(HFLog::HF_ERROR, "CURRENTLY REMOVING COMPONENTS IS NOT IMPLEMENTED", __FILE__, __LINE__); }

void Game::RemoveCollisionComponent(Component* component) { g_Logger.Log(HFLog::HF_ERROR, "CURRENTLY REMOVING COMPONENTS IS NOT IMPLEMENTED", __FILE__, __LINE__); }