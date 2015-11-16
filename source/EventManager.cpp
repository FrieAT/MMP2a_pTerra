#include "EventManager.h"

std::vector<std::shared_ptr<IEventObserver>> EventManager::Observers = *new std::vector<std::shared_ptr<IEventObserver>>();

void EventManager::Update(sf::RenderWindow &window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        /////// TODO: Call GameStateManager, if exit occurs !!! ///////////////
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        /////////////////////////////////////////////////////////////////////
        
        EventManager::UpdateEventObserver(event);
    }
}

void EventManager::RegisterEventObserver(IEventObserver &observer)
{
    std::shared_ptr<IEventObserver>* ref = new std::shared_ptr<IEventObserver>(&observer);
    EventManager::Observers.push_back(*ref);
}

void EventManager::UnregisterEventObserver(IEventObserver &observer)
{
    for(unsigned int i = 0; i < EventManager::Observers.size(); i++) {
        if(EventManager::Observers[i].get() != &observer) { continue; }
        EventManager::Observers.erase(EventManager::Observers.begin() + i);
        break;
    }
}

void EventManager::UpdateEventObserver(sf::Event event)
{
    for(unsigned int i = 0; i < EventManager::Observers.size(); i++) {
        EventManager::Observers[i]->OnEventUpdate(event);
    }
}