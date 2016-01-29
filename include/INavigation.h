/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "IComponent.h"

class INavigation : public IComponent
{
public:
    INavigation() : m_bActive(false), m_bTerraFound(false) { }
    virtual void SetNavigationPoint(sf::Vector2f PointPosition) = 0;
    virtual sf::Vector2f GetNavigationPoint() = 0;
    virtual void SetNavigationActive(bool bActive, bool bForce = false) = 0;
	virtual void SetNavigationCursorColor(sf::Color Color) = 0;
    virtual bool IsNavigationActive() { return m_bActive; }
    virtual float GetDistanceToPoint() { return m_fDistance; }
	virtual bool FoundTerra() { return m_bTerraFound;  }
    
    virtual void Serialize(SerializeNode* pParentNode)
    {
        this->IComponent::Serialize(pParentNode);
        pParentNode->AddElement(new SerializeNode("NavigationPointX", ESerializeNodeType::Property, std::to_string(m_NavigationPoint.x)));
        pParentNode->AddElement(new SerializeNode("NavigationPointY", ESerializeNodeType::Property, std::to_string(m_NavigationPoint.y)));
        pParentNode->AddElement(new SerializeNode("Active", ESerializeNodeType::Property, std::to_string(m_bActive)));
		pParentNode->AddElement(new SerializeNode("TerraFound", ESerializeNodeType::Property, std::to_string(m_bTerraFound)));
    }
    static void Deserialize(SerializeNode* pNode, INavigation* pParentComponent)
    {
        float x = stof((pNode->GetNode("NavigationPointX"))->GetValue());
        float y = stof((pNode->GetNode("NavigationPointY"))->GetValue());
        pParentComponent->m_NavigationPoint = sf::Vector2f(x, y);
        
        int active = stoi((pNode->GetNode("Active"))->GetValue());
		pParentComponent->m_bActive = (active ? true : false);

		int terrafound = stoi((pNode->GetNode("TerraFound")->GetValue()));
		pParentComponent->m_bTerraFound = (terrafound ? true : false);
    }
    EComponentType GetComponentType()
    {
        return EComponentType::Navigation;
    }
    virtual std::string GetComponentName() { return std::string("INavigation"); }
protected:
    sf::Vector2f m_NavigationPoint;
    bool m_bActive;
    float m_fDistance;
	bool m_bTerraFound;
};