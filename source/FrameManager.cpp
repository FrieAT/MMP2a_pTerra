#include "FrameManager.h"
#include <memory>

std::vector<IFrameObserver*> FrameManager::Observers;

void FrameManager::Update(sf::Time deltaTime)
{
    for (unsigned int i = 0; i < Observers.size(); i++)
    {
        Observers[i]->OnFrameUpdate(deltaTime);
    }
}

void FrameManager::Draw(sf::RenderWindow* window)
{
    for (unsigned int i = 0; i < Observers.size(); i++)
    {
        Observers[i]->OnFrameDraw(window);
    }
}

void FrameManager::RegisterEventObserver(IFrameObserver* observer)
{
	Observers.push_back(observer);
}

void FrameManager::UnregisterEventObserver(IFrameObserver* observer)
{
    for(int i = 0; i < Observers.size(); i++)
    {
        if(Observers[i] != observer) continue;
        Observers.erase(Observers.begin() + i);
        break;
    }
}

void FrameManager::Clear()
{
	Observers.clear();
}