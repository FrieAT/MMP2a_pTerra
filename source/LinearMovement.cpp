/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "LinearMovement.h"
#include "GameObject.h"
#include "IPosition.h"

LinearMovement::LinearMovement(float fRotation, sf::Vector2f ShipSpeed)
{
	FrameManager::GetInstance().RegisterEventObserver(this);
	sf::Transform RotationMatrice = sf::Transform::Identity;
	RotationMatrice.rotate(fRotation);
	m_fRotation = fRotation;
	m_fSpeed = 200.f;
	m_Direction = RotationMatrice*(sf::Vector2f(0, -1));
	m_Movement = ShipSpeed;
}

LinearMovement::~LinearMovement()
{
    FrameManager::GetInstance().UnregisterEventObserver(this);
}


void LinearMovement::OnFrameUpdate(sf::Time DeltaTime)
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	pPositionComponent->SetRotation(m_fRotation);
	m_Movement = m_Direction * m_fSpeed* DeltaTime.asSeconds();
	pPositionComponent->SetPosition(pPositionComponent->GetPosition()+ m_Movement);
}

