#include "EventManager.h"

std::vector<IEventObserver*> EventManager::Observers;

void EventManager::Update(sf::RenderWindow* window)
{
	//sf::Event event;
	//while(window.pollEvent(event))
	//{
	//    /////// TODO: Call GameStateManager, if exit occurs !!! ///////////////
	//    // Close window: exit
	//    //if (event.type == sf::Event::Closed) {
	//    //    window.close();
	//    //}
	//    

	//    /////////////////////////////////////////////////////////////////////
	//    
	//    EventManager::UpdateEventObserver(event);
	//}
}

void EventManager::RegisterEventObserver(IEventObserver* observer)
{
	Observers.push_back(observer);
}

void EventManager::UnregisterEventObserver(IEventObserver* observer)
{
	for (unsigned int i = 0; i < Observers.size(); i++)
	{
		if (Observers[i] != observer) continue;
		Observers.erase(Observers.begin() + i);
		break;
	}
}

void EventManager::UnregisterAllEventObserver()
{
    Observers.clear();
}

void EventManager::UpdateEventObserver(sf::Event event)
{
	for (unsigned int i = 0; i < Observers.size(); i++)
	{
		Observers[i]->OnEventUpdate(event);
	}
}