/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "InputManager.h"
#include <iostream>

void InputManager::Update(sf::RenderWindow* pWindow, tgui::Gui* pGui)
{
	sf::Event Event;
	while (pWindow->pollEvent(Event))
	{
		pGui->handleEvent(Event);

		std::string strMovement = "";

		// Escape pressed: exit
		if (Event.key.code == sf::Keyboard::Escape)
		{
			pWindow->close();//TODO call game exit
		}
		if (Event.type == sf::Event::Closed)
		{
			pWindow->close();//TODO call game exit
		}

		//Left
		if (Event.key.code == sf::Keyboard::Left)
		{
			strMovement = "1LEFT";
		}
		if (Event.key.code == sf::Keyboard::A)
		{
			strMovement = "2LEFT";
		}

		//Right
		if (Event.key.code == sf::Keyboard::Right)
		{
			strMovement = "1RIGHT";
		}
		if (Event.key.code == sf::Keyboard::D)
		{
			strMovement = "2RIGHT";
		}

		//Up
		if (Event.key.code == sf::Keyboard::Up)
		{
			strMovement = "1UP";
		}
		if (Event.key.code == sf::Keyboard::W)
		{
			strMovement = "2UP";
		}

		//Down
		if (Event.key.code == sf::Keyboard::Down)
		{
			strMovement = "1DOWN";
		}
		if (Event.key.code == sf::Keyboard::S)
		{
			strMovement = "2DOWN";
		}

        //Fire
        if (Event.key.code == sf::Keyboard::Space)
        {
            strMovement = "2FIRE";
        }
		if (Event.key.code == sf::Keyboard::Numpad0)
		{
			strMovement = "1FIRE";
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



