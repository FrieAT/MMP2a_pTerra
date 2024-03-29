/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "CircleCollision.h"
#include "CollisionManager.h"

CircleCollision::CircleCollision(float fRadius)
: m_fRadius(fRadius)
{

}

CircleCollision::~CircleCollision()
{
	CollisionManager::GetInstance().UnregisterCollisionbody(this);
	FrameManager::GetInstance().UnregisterEventObserver(this);

}

void CircleCollision::Init()
{
    CollisionManager::GetInstance().RegisterCollisionbody(this);
    FrameManager::GetInstance().RegisterEventObserver(this);
}

bool CircleCollision::colliding(ICollision* pCollisionBody)
{
	CircleCollision* pOther = static_cast<CircleCollision*> (pCollisionBody);
    IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    IPosition* pPositionOtherComponent = static_cast<IPosition*>(pCollisionBody->GetAssignedGameObject()->GetComponent(EComponentType::Position));
    
    if(pPositionComponent == nullptr || pPositionOtherComponent == nullptr)
    {
        m_bHit = false;
        return false;
    }
    
	sf::Vector2f lenght_vec = pPositionOtherComponent->GetPosition() - pPositionComponent->GetPosition();
	
	float fLength = lenght_vec.x*lenght_vec.x + lenght_vec.y*lenght_vec.y;
	float fDistance = m_fRadius + pOther->m_fRadius;
	fDistance = fDistance*fDistance;

	if (fLength < fDistance)
	{
		m_bHit = true;
		CollisionEvent col_ev;
		col_ev.Body1 = this->GetAssignedGameObject();
		col_ev.Body2 = pOther->GetAssignedGameObject();
		col_ev.normal =  -(lenght_vec/4.f); 
		CollisionManager::GetInstance().m_CollisonEvents.push(col_ev);
		return true;
	}
	else
	{
		m_bHit = false;
		return false;
	}
}

void CircleCollision::OnFrameDraw(sf::RenderWindow* pWindow)
{
    IPosition* pos = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	sf::CircleShape test(m_fRadius);
	if(m_bHit) test.setFillColor(sf::Color::Magenta);
	else test.setFillColor(sf::Color::Blue);
	test.setPosition(pos->GetPosition()- sf::Vector2f(m_fRadius, m_fRadius));
	
	// pWindow->draw(test);
}

void CircleCollision::Serialize(SerializeNode *pParentNode)
{
    this->ICollision::Serialize(pParentNode);
    pParentNode->AddElement(new SerializeNode("Radius", ESerializeNodeType::Property, std::to_string(m_fRadius)));
    pParentNode->AddElement(new SerializeNode("Hit", ESerializeNodeType::Property, std::to_string(m_bHit)));
}

IComponent* CircleCollision::Deserialize(SerializeNode* pNode)
{
    float fRadius = stof((pNode->GetNode("Radius"))->GetValue());
    int bHit = stoi((pNode->GetNode("Hit"))->GetValue());
    
    CircleCollision* pComponent = new CircleCollision(fRadius);
    pComponent->m_bHit = (bHit ? true : false);
    
    return pComponent;
}