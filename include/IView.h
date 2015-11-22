#pragma once

#include "IComponent.h"

class IView : public IComponent
{
public:
    // STUB: Currently no information about what a IView should have.
    
    EComponentType GetComponentType()
    {
        return EComponentType::View;
    }
protected:
    
};