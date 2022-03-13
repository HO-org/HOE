#include "game.h"
#include "hflog.h"
#include <algorithm>

bool Game::ComponentInVector(Component* component, std::vector<Component*> v)
{
    if (
        std::find_if(v.begin(), v.end(), [component](Component* c) { return c == component; }) != v.end()
    ) { return true; }

    return false;
}


void Game::AddComponent(Component* component, CallbackType type)
{
    switch (type)
    {
        case UPDATE:
            if (ComponentInVector(component, m_UpdateComponents)) 
            { 
                HFLog::Log("Component already registered as an update component!");
                break;
            }


            m_UpdateComponents.push_back(component);
            component->registeredWhere = UPDATE;
            // HFLog::Log("so far so good");
            break;

        case READY:
            if (ComponentInVector(component, m_ReadyComponents)) 
            { 
                HFLog::Log("Component already registered as a ready component!");
                break;
            }

            m_ReadyComponents.push_back(component);
            component->registeredWhere = READY;
            break;

        case READYUPDATE:
            if (ComponentInVector(component, m_UpdateComponents) || ComponentInVector(component, m_ReadyComponents)) 
            { 
                HFLog::Log("Component already registered as an update/ready component!");
                break;
            }

            m_ReadyComponents.push_back(component);
            m_UpdateComponents.push_back(component);
            component->registeredWhere = READYUPDATE;
            break;

        default:
            HFLog::Log("Tried to add a component with an invalid type passed");
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
        HFLog::Log("Component already registered as a render component!");
        return;
    }

    m_RenderComponents.push_back(component);

    switch (component->registeredWhere)
    {
        case RENDER:
            component->registeredWhere = RENDER;
            break;

        case READY:
            component->registeredWhere = READYRENDER;
            break;
        
        case UPDATE:
            component->registeredWhere = UPDATERENDER;
            break;

        case READYUPDATE:
            component->registeredWhere = READYUPDATERENDER;
            break;
        
        default:
            HFLog::Log("Tried to add a render component with an invalid type passed");
            break;
    }
}

void Game::AddCollisionComponent(CollisionComponent* component)
{
    // if ( std::find(m_CollisionComponents.begin(), m_CollisionComponents.end(), component) != m_CollisionComponents.end() )
    if (
        std::find_if(m_CollisionComponents.begin(), m_CollisionComponents.end(), [component](CollisionComponent* c) { return c == component; }) != m_CollisionComponents.end()
    )
    {
        HFLog::Log("Component already registered as a collision component!");
        return;
    }

    m_CollisionComponents.push_back(component);

    switch (component->registeredWhere)
    {
        case COLLISION:
            component->registeredWhere = COLLISION;
            break;

        case READY:
            component->registeredWhere = READYCOLLISION;
            break;
        
        case UPDATE:
            component->registeredWhere = UPDATECOLLISION;
            break;

        case READYUPDATE:
            component->registeredWhere = READYUPDATECOLLISION;
            break;
        
        default:
            HFLog::Log("Tried to add a collision component with an invalid type passed");
            break;
    }
}


void Game::RemoveComponent(Component* component, CallbackType type)
{

}

void Game::RemoveRenderComponent(Component* component) {}

void Game::RemoveCollisionComponent(Component* component) {}