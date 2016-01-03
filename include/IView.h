/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

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
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
    }
protected:
    
};