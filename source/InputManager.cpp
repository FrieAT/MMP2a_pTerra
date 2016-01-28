/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "InputManager.h"
#include "Game.h"
#include "SoundManager.h"

void InputManager::Update(sf::RenderWindow* pWindow, tgui::Gui* pGui)
{
	sf::Event Event;
	while (pWindow->pollEvent(Event))
	{
		pGui->handleEvent(Event);

		std::string strMovement = "";

		// Escape pressed: Pause
		if (Event.key.code == sf::Keyboard::Escape)
		{
			Game::m_pEngine->StoreCurrentState();
			Game::m_pEngine->ChangeState(EGameState::GameStatePause);
			//pWindow->close(); //TODO call game exit
		}

		// Window closed: Exit
		if (Event.type == sf::Event::Closed)
		{
			pWindow->close(); //TODO call game exit
		}

		//Left
		if (Event.key.code == sf::Keyboard::A || Event.key.code == sf::Keyboard::Left)
		{
			strMovement = "LEFT";
		}

		//Right
		if (Event.key.code == sf::Keyboard::D || Event.key.code == sf::Keyboard::Right)
		{
			strMovement = "RIGHT";
		}

		//Up
		if (Event.key.code == sf::Keyboard::W || Event.key.code == sf::Keyboard::Up)
		{
			strMovement = "UP";
		}

		//Down
		if (Event.key.code == sf::Keyboard::S || Event.key.code == sf::Keyboard::Down)
		{
			strMovement = "DOWN";
		}

        //Fire
        if (Event.key.code == sf::Keyboard::Space || Event.key.code == sf::Keyboard::Numpad0)
        {
            strMovement = "FIRE";
        }

		//pressed
		if (Event.type == sf::Event::KeyPressed)
		{
			strMovement.append("_P");
		}
		//released
		if (Event.type == sf::Event::KeyReleased)
		{
			strMovement.append("_R");
		}

		if (strMovement.size() > 1)
		{
			UpdateEventObserver(strMovement);
		}
	}
}

void InputManager::RegisterEventObserver(IInputObserver* pObserver)
{
	m_Observers.push_back(pObserver);
}

void InputManager::UnregisterEventObserver(IInputObserver* pObserver)
{
    for(unsigned int i = 0; i < m_Observers.size(); i++)
    {
        if(m_Observers[i] != pObserver) continue;
        m_Observers.erase(m_Observers.begin() + i);
        break;
    }
}

void InputManager::UpdateEventObserver(std::string strEvent)
{
	for (unsigned int i = 0; i < m_Observers.size(); i++)
	{
        m_Observers[i]->OnInputUpdate(strEvent);
	}
}

void InputManager::Clear()
{
	m_Observers.clear();
	m_Observers.shrink_to_fit();
}



