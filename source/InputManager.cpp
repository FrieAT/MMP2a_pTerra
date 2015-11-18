#include "InputManager.h"
#include <iostream>

std::vector<std::shared_ptr<IInputObserver>> InputManager::Observers = *new std::vector<std::shared_ptr<IInputObserver>>();


InputManager::InputManager()
{
}

void InputManager::Update(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		std::string movement = "";

		// Escape pressed: exit
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();//TODO call game exit
		}
		if (event.type == sf::Event::Closed)
		{
			window.close();//TODO call game exit
		}


		//Left
		if (event.key.code == sf::Keyboard::Left)
		{
			movement = "LEFT";
		}
		if (event.key.code == sf::Keyboard::A)
		{
			movement = "LEFT";
		}
		//Right
		if (event.key.code == sf::Keyboard::Right)
		{
			movement = "RIGHT";
		}
		if (event.key.code == sf::Keyboard::D)
		{
			movement = "RIGHT";
		}
		//Up
		if (event.key.code == sf::Keyboard::Up)
		{
			movement = "UP";
		}
		if (event.key.code == sf::Keyboard::W)
		{
			movement = "UP";
		}
		//Down
		if (event.key.code == sf::Keyboard::Down)
		{
			movement = "DOWN";
		}
		if (event.key.code == sf::Keyboard::S)
		{
			movement = "DOWN";
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
			InputManager::UpdateEventObserver(movement);
		}
	}
}

void InputManager::RegisterEventObserver(IInputObserver &observer)
{
	std::shared_ptr<IInputObserver>* ref = new std::shared_ptr<IInputObserver>(&observer);
	InputManager::Observers.push_back(*ref);
}

void InputManager::UnregisterEventObserver(IInputObserver &observer)
{
	for (unsigned int i = 0; i < InputManager::Observers.size(); i++)
	{
		if (InputManager::Observers[i].get() != &observer) continue;
		InputManager::Observers.erase(InputManager::Observers.begin() + i);
		break;
	}
}

void InputManager::UpdateEventObserver(std::string event)
{
	for (unsigned int i = 0; i < InputManager::Observers.size(); i++)
	{
		InputManager::Observers[i]->OnInputUpdate(event);
	}
}



