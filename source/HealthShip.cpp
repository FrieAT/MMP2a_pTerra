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
#include "INavigation.h"

HealthShip::HealthShip(float fHealth)
: IHealth()
{
	this->m_fHealth = fHealth;
    m_pHealthDebug = GameObjectFactory::CreateFontText(sf::Vector2f(0.f,0.f), "assets/Starjedi.ttf", "", 8);
    m_pHealthDebug->SetTemporaryState(true);
    m_pHealthDebug->SetAssistedState(true);
}

void HealthShip::Init()
{
    IHealth::Init();
    FrameManager::GetInstance().RegisterEventObserver(this);
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

HealthShip::~HealthShip()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
    m_pHealthDebug->SetAssistedState(false);
    ObjectManager::GetInstance().RemoveGameObject(m_pHealthDebug);
}



void HealthShip::Damage(float fDamage)
{
    IHealth::Damage(fDamage);
	if (m_fHealth <= 0.f)
	{
		// Hier wird das Schiff nicht zerstört, weil es sowieso einen GameState-Switch auslöst.
		// ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
        
        Game::m_pEngine->ChangeState(new GameStateGameOver());
	}
}

void HealthShip::OnFrameDraw(sf::RenderWindow* pWindow)
{

}

void HealthShip::OnFrameUpdate(sf::Time DeltaTime)
{
    IHealth::RegenerateShield(DeltaTime);
    
    IPosition* pPositionTextComponent = static_cast<IPosition*>(m_pHealthDebug->GetComponent(EComponentType::Position));
    IPosition* pPositionShipComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
    IDrawing* pDrawingTextComponent = static_cast<IDrawing*>(m_pHealthDebug->GetComponent(EComponentType::Drawing));
    INavigation* pNavigation = static_cast<INavigation*>(GetAssignedGameObject()->GetComponent(EComponentType::Navigation));
    
    sf::Vector2f ship_pos = pPositionShipComponent->GetPosition() + sf::Vector2f(-30.f, 50.f);
    std::stringstream health_text;
    health_text << "Health: " << m_fHealth << "\nShield: " << m_fShield;
    if(pPositionShipComponent != nullptr)
    {
        health_text << "\nPosition: (" << round(pPositionShipComponent->GetPosition().x) << " / " << round(pPositionShipComponent->GetPosition().y) << ")";
    }
    if(pNavigation != nullptr && pNavigation->IsNavigationActive())
    {
        health_text << "\nNavi: " << pNavigation->GetDistanceToPoint() << " Meters";
    }
    pPositionTextComponent->SetPosition(ship_pos);
    pDrawingTextComponent->SetText(health_text.str());
}

void HealthShip::OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact)
{
    float impulse_length = sqrt(ImpulseImpact.x * ImpulseImpact.x + ImpulseImpact.y * ImpulseImpact.y);
    
    // std::cout << "Detected Collision with a " << pOther->GetID() << " (Impulse: " << impulse_length << ")" << std::endl;
    Damage(impulse_length / 10000 );
}

IComponent* HealthShip::Deserialize(SerializeNode *pNode)
{
    HealthShip* pComponent = new HealthShip(0.f); // Only properties from own class, should be handled in Deserialize!
    
    IHealth::Deserialize(pNode, pComponent);
    
    return pComponent;
}