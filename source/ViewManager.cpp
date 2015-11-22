#include "ViewManager.h"

std::vector<IViewObserver*> ViewManager::Observers;

void ViewManager::Update(sf::Time deltaTime)
{
    for (unsigned int i = 0; i < Observers.size(); i++)
    {
        Observers[i]->OnEventUpdate(deltaTime);
    }
}

void ViewManager::Draw(sf::RenderWindow *window)
{
    for (unsigned int i = 0; i < Observers.size(); i++)
    {
        Observers[i]->OnEventDraw(window);
    }
}

void ViewManager::RegisterEventObserver(IViewObserver* observer)
{
    Observers.push_back(observer);
}

void ViewManager::UnregisterEventObserver(IViewObserver* observer)
{
    for (unsigned int i = 0; i < Observers.size(); i++)
    {
        if (Observers[i] != observer) continue;
        Observers.erase(Observers.begin() + i);
        break;
    }
}