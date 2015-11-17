#include "InputManager.h"

std::vector<std::shared_ptr<IInputObserver>> InputManager::Observers = *new std::vector<std::shared_ptr<IInputObserver>>();


InputManager::InputManager()
{
}

void InputManager::Update(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Escape pressed: exit
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window.close();//TODO call game exit
		}
		//Left
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Left)
		{

		}
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::A)
		{

		}
		//Right
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Right)
		{

		}
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::D)
		{

		}
		//Up
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Up)
		{

		}
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::W)
		{

		}
		//Down
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Down)
		{

		}
		if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::S)
		{

		}


		InputManager::UpdateEventObserver(event);
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

void InputManager::UpdateEventObserver(sf::Event event)
{
	for (unsigned int i = 0; i < InputManager::Observers.size(); i++)
	{
		InputManager::Observers[i]->OnInputUpdate(event);
	}
}



