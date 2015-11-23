#include "InputManager.h"
#include <iostream>


void InputManager::Update(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		std::string movement = "";

		// Escape pressed: exit
		if (event.key.code == sf::Keyboard::Escape)
		{
			
			window->close();//TODO call game exit
		}
		if (event.type == sf::Event::Closed)
		{
			window->close();//TODO call game exit
		}


		//Left
		if (event.key.code == sf::Keyboard::Left)
		{
			movement = "1LEFT";
		}
		if (event.key.code == sf::Keyboard::A)
		{
			movement = "2LEFT";
		}
		//Right
		if (event.key.code == sf::Keyboard::Right)
		{
			movement = "1RIGHT";
		}
		if (event.key.code == sf::Keyboard::D)
		{
			movement = "2RIGHT";
		}
		//Up
		if (event.key.code == sf::Keyboard::Up)
		{
			movement = "1UP";
		}
		if (event.key.code == sf::Keyboard::W)
		{
			movement = "2UP";
		}
		//Down
		if (event.key.code == sf::Keyboard::Down)
		{
			movement = "1DOWN";
		}
		if (event.key.code == sf::Keyboard::S)
		{
			movement = "2DOWN";
		}
        //Fire
        if (event.key.code == sf::Keyboard::Space)
        {
            movement = "1FIRE";
        }
		if (event.key.code == sf::Keyboard::Numpad0)
		{
			movement = "2FIRE";
		}

		//pressed
		if (event.type == sf::Event::KeyPressed)
		{
			movement.append("_P");
		}
		//released
		if (event.type == sf::Event::KeyReleased)
		{
			movement.append("_R");
		}

		if (movement.size() > 1)
		{
			UpdateEventObserver(movement);
		}
	}
}

void InputManager::RegisterEventObserver(IInputObserver* observer)
{
	Observers.push_back(observer);
}

void InputManager::UnregisterEventObserver(IInputObserver* observer)
{
    for(int i = 0; i < Observers.size(); i++)
    {
        if(Observers[i] != observer) continue;
        Observers.erase(Observers.begin() + i);
        break;
    }
}

void InputManager::UpdateEventObserver(std::string event)
{
	for (unsigned int i = 0; i < Observers.size(); i++)
	{
        Observers[i]->OnInputUpdate(event);
	}
}

void InputManager::Clear()
{
	Observers.clear();
	Observers.shrink_to_fit();
}



