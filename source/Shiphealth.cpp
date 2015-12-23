/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/
#pragma once

#include <math.h>
#include <sstream>

#include "Shiphealth.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "GameObjectFactory.h"

Shiphealth::Shiphealth(float fHealth)
{
	this->m_fHealth = fHealth;
	FrameManager::GetInstance().RegisterEventObserver(this);
    m_pHealthDebug = GameObjectFactory::CreateFontText(sf::Vector2f(0.f,0.f), "assets/Starjedi.ttf", "", 8);
    ObjectManager::GetInstance().AddGameObject(m_pHealthDebug);
}

void Shiphealth::Init()
{
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

Shiphealth::~Shiphealth()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
    ObjectManager::GetInstance().RemoveGameObject(m_pHealthDebug);
}



void Shiphealth:: damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO destroy Ship and remove end game
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
	}
}

void Shiphealth::OnFrameDraw(sf::RenderWindow* pWindow)
{
    
}

void Shiphealth::OnFrameUpdate(sf::Time DeltaTime)
{
    IPosition* pPositionTextComponent = static_cast<IPosition*>(m_pHealthDebug->GetComponent(EComponentType::Position));
    IPosition* pPositionShipComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    IDrawing* pDrawingTextComponent = static_cast<IDrawing*>(m_pHealthDebug->GetComponent(EComponentType::Drawing));
    
    sf::Vector2f ship_pos = pPositionShipComponent->GetPosition() + sf::Vector2f(-30.f, 50.f);
    std::stringstream health_text;
    health_text << std::string("Health: ") << m_fHealth;
    pPositionTextComponent->SetPosition(ship_pos);
    pDrawingTextComponent->SetText(health_text.str());
}

void Shiphealth::OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact)
{
    float impulse_length = sqrt(ImpulseImpact.x * ImpulseImpact.x + ImpulseImpact.y * ImpulseImpact.y);
   
    // Ignore invalid Impulse Length´s
    if(impulse_length >= 500.f)
    {
        return;
    }
    
    std::cout << "Detected Collision with a " << pOther->GetID() << " (Impulse: " << impulse_length << ")" << std::endl;
    damage(impulse_length / 1000 );
}
