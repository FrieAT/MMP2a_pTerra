#pragma once

#include "IComponent.h"

class IView : public IComponent
{
public:
    virtual sf::FloatRect GetViewport() = 0;
    
    EComponentType GetComponentType()
    {
        return EComponentType::View;
    }
protected:
    
};