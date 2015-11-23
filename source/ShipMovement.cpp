/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "ShipMovement.h"
#include "GameObjectFactory.h"
#include "ObjectManager.h"

ShipMovement::ShipMovement(char cPlayer)
{
	InputManager::GetInstance().RegisterEventObserver(this);
	FrameManager::GetInstance().RegisterEventObserver(this);
	this->m_cPlayer = cPlayer;

	m_Impulses.resize(5);
	m_fAcceleration = 1.f;
	m_fMaxSpeed = 11000;
}


ShipMovement::~ShipMovement()
{
    InputManager::GetInstance().UnregisterEventObserver(this);
    FrameManager::GetInstance().UnregisterEventObserver(this);
}


void ShipMovement::OnInputUpdate(std::string strEvent)
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	if (strEvent[0] != m_cPlayer)
	{
		return;
	}
	strEvent = strEvent.substr(1);

	if(strEvent=="RIGHT_P")
	{
		pPositionComponent->SetRotation(pPositionComponent->GetRotation() + 5);
	}
	if (strEvent == "LEFT_P")
	{
		pPositionComponent->SetRotation(pPositionComponent->GetRotation() - 5);
	}
	if (strEvent == "UP_P")
	{
		m_Direction = sf::Vector2f(0.f, -0.8f);
	}
	if (strEvent == "DOWN_P")
	{
		m_Direction = sf::Vector2f(0.f, 0.6f);
	}

	if (strEvent == "UP_R" || strEvent == "DOWN_R")
	{
		m_Direction = sf::Vector2f(0.f, 0.f);
	}

	//TODO make a own weapon component
	if (strEvent == "FIRE_P")
	{
  		ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateMissile(pPositionComponent,m_Impulses[0]));
	}
}


void ShipMovement::UpdateMovement()
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	sf::Transform RotationMatrice = sf::Transform::Identity;
	RotationMatrice.rotate(pPositionComponent->GetRotation());

	m_Impulses[0] = m_Impulses[0] + RotationMatrice * m_Direction * m_fAcceleration;

	float fSpeed = m_Impulses[0].x*m_Impulses[0].x + m_Impulses[0].y * m_Impulses[0].y;

	if (fSpeed >= m_fMaxSpeed)
	{
		m_Impulses[0] = m_Impulses[0] * 0.99f;
	}

	//std::cout << speed << std::endl;

}



void ShipMovement::OnFrameUpdate(sf::Time DeltaTime)
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	sf::Vector2f Movement;

	UpdateMovement();

	for (unsigned int i = 0; i < m_Impulses.size();i++)
	{
		Movement += m_Impulses[i];
	}

	pPositionComponent->SetPosition(pPositionComponent->GetPosition() + Movement * DeltaTime.asSeconds());

}
