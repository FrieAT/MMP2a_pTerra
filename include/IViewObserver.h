#pragma once

class IViewObserver
{
public:
    virtual void OnEventUpdate(sf::Time delta_time) = 0;
    virtual void OnEventDraw(sf::RenderWindow* window) = 0;
};