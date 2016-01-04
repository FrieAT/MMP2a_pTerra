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
    static void Deserialize(SerializeNode* pNode, IView* pParentComponent)
    {
        // Nothing to extract here...
    }
    virtual std::string GetComponentName() { return std::string("IView"); }
protected:
    
};