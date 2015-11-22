#pragma once

#include "IComponent.h"

class IView : public IComponent
{
public:
    virtual void Update() = 0;
    virtual void Draw(sf::RenderWindow* window) = 0;
    
    EComponentType GetComponentType()
    {
        return EComponentType::View;
    }
protected:
    
};