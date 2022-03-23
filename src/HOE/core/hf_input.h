#include "game.h"
#include "SDL.h"
#include <vector>
#include <algorithm>

// Singleton class
class HFInput
{
public:
    bool m_Quit = false;

    int UpdateDownKeys()
    {
        SDL_Event event;

        m_DownKeysThisUpdate.clear();
        m_DownKeysInput.clear();

        while(SDL_PollEvent(&event))
        {
            if (event.key.type == SDL_QUIT) { m_Quit = true; }

            if(event.key.type == SDL_KEYDOWN)
            {
                SDL_Keycode keyCode = event.key.keysym.sym;

                if(!IsKeyDown(keyCode))
                {
                    m_DownKeysThisUpdate.push_back(keyCode);
                    m_DownKeys.push_back(keyCode);
                }

                m_DownKeysInput.push_back(keyCode);

            }
            else if (event.key.type == SDL_KEYUP)
            {
                SetKeyUp(event.key.keysym.sym);
            }
        }

        return 0;
    }


    bool IsKeyDown(SDL_Keycode key)
    {
        for (SDL_Keycode keyCode : m_DownKeys)
        {
            if (keyCode == key)
            {
                return true;
            }
        }

        return false;
    }

    bool IsKeyInput(SDL_Keycode key)
    {
        for (SDL_Keycode keyCode : m_DownKeysInput)
        {
            if (keyCode == key)
            {
                return true;
            }
        }

        return false;
    }

    bool IsKeyJustDown(SDL_Keycode key)
    {
        for (SDL_Keycode keyCode : m_DownKeysThisUpdate)
        {
            if (keyCode == key)
            {
                return true;
            }
        }

        return false;
    }

private:
    std::vector<SDL_Keycode> m_DownKeys;
    std::vector<SDL_Keycode> m_DownKeysThisUpdate;
    std::vector<SDL_Keycode> m_DownKeysInput;

    void SetKeyUp(SDL_Keycode key)
    {
        m_DownKeys.erase( std::remove_if(m_DownKeys.begin(), m_DownKeys.end(), [key](SDL_Keycode value){ return value == key; } ), m_DownKeys.end() );
    }

private:
    HFInput() {} ;

public:
    static HFInput& GetInstance()
    {
        static HFInput instance;

        return instance;
    }

    HFInput(HFInput const&) = delete;
    void operator=(HFInput const&) = delete;
};