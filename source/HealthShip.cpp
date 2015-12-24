/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include <math.h>
#include <sstream>

#include "HealthShip.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "GameObjectFactory.h"
#include "GameStateGameOver.h"
#include "Game.h"

HealthShip::HealthShip(float fHealth)
{
	this->m_fHealth = fHealth;
	FrameManager::GetInstance().RegisterEventObserver(this);
    m_pHealthDebug = GameObjectFactory::CreateFontText(sf::Vector2f(0.f,0.f), "assets/Starjedi.ttf", "", 8);
}

void HealthShip::Init()
{
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

HealthShip::~HealthShip()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
    delete(m_pHealthDebug);
    m_pHealthDebug = nullptr;
}



void HealthShip::Damage(float fDamage)
{
	m_fHealth -= fDamage;
	if (m_fHealth < 0)
	{
		//TODO destroy Ship and remove end game
		ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
        
        Game::m_pEngine->ChangeState(new GameStateGameOver());
	}
}

void HealthShip::OnFrameDraw(sf::RenderWindow* pWindow)
{
    IDrawing* pHealthDebugDrawing = static_cast<IDrawing*>(m_pHealthDebug->GetComponent(EComponentType::Drawing));
    pHealthDebugDrawing->Draw(pWindow);
}

void HealthShip::OnFrameUpdate(sf::Time DeltaTime)
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

void HealthShip::OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact)
{
    float impulse_length = sqrt(ImpulseImpact.x * ImpulseImpact.x + ImpulseImpact.y * ImpulseImpact.y);
    
    // std::cout << "Detected Collision with a " << pOther->GetID() << " (Impulse: " << impulse_length << ")" << std::endl;
    Damage(impulse_length / 10000 );
}