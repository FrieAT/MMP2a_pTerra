/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include <math.h>
#include <sstream>

#include "HealthAsteroid.h"
#include "ObjectManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "GameObjectFactory.h"
#include "GameStateIntro.h"
#include "Game.h"

HealthAsteroid::HealthAsteroid(float fHealth)
{
    this->m_fHealth = fHealth;
    m_pHealthDebug = GameObjectFactory::CreateFontText(sf::Vector2f(0.f,0.f), "assets/Starjedi.ttf", "", 8);
}

HealthAsteroid::~HealthAsteroid()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
    CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
    ObjectManager::GetInstance().RemoveGameObject(m_pHealthDebug);
    m_pHealthDebug = nullptr;
}

void HealthAsteroid::Init()
{
    FrameManager::GetInstance().RegisterEventObserver(this);
    CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

void HealthAsteroid::Damage(float fDamage)
{
    m_fHealth -= fDamage;
    if (m_fHealth < 0)
    {
        WorldManager::GetInstance().SaveGame("savegame.txt"); // DEBUG: For testing purpose create savegame every-time when asteroid will be deleted.
        
        //TODO destroy Ship and remove end game
        ObjectManager::GetInstance().RemoveGameObject(GetAssignedGameObject());
    }
}

void HealthAsteroid::OnFrameDraw(sf::RenderWindow* pWindow)
{
    IDrawing* pHealthDebugDrawing = static_cast<IDrawing*>(m_pHealthDebug->GetComponent(EComponentType::Drawing));
    pHealthDebugDrawing->Draw(pWindow);
}

void HealthAsteroid::OnFrameUpdate(sf::Time DeltaTime)
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

void HealthAsteroid::OnCollisionEvent(GameObject* pOther, sf::Vector2f ImpulseImpact)
{
    float impulse_length = sqrt(ImpulseImpact.x * ImpulseImpact.x + ImpulseImpact.y * ImpulseImpact.y);
    
    // std::cout << "Detected Collision with a " << pOther->GetID() << " (Impulse: " << impulse_length << ")" << std::endl;
    Damage(impulse_length / 10000 );
}

IComponent* HealthAsteroid::Deserialize(SerializeNode *pNode)
{
    HealthAsteroid* pComponent = new HealthAsteroid(0.f); // Only properties from own class, should be handled in Deserialize!
    
    IHealth::Deserialize(pNode, pComponent);
    
    return pComponent;
}