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
	m_shipstates = std::vector<bool>(5, false);
	m_fAcceleration = 2.f;
	m_fMaxSpeed = 200000;
	m_fFirerate = 60;
}


ShipMovement::~ShipMovement()
{
    InputManager::GetInstance().UnregisterEventObserver(this);
    FrameManager::GetInstance().UnregisterEventObserver(this);
}


void ShipMovement::OnInputUpdate(std::string strEvent)
{
	if (strEvent[0] != m_cPlayer)
	{
		return;
	}
	strEvent = strEvent.substr(1);

	if (strEvent == "RIGHT_P")
	{
		m_shipstates[0] = true;
	}
	if (strEvent == "RIGHT_R")
	{
		m_shipstates[0] = false;
	}


	if (strEvent == "LEFT_P")
	{
		m_shipstates[1] = true;
	}
	if (strEvent == "LEFT_R")
	{
		m_shipstates[1] = false;
	}


	if (strEvent == "UP_P")
	{
		m_shipstates[2] = true;
	}
	if (strEvent == "UP_R")
	{
		m_shipstates[2] = false;
	}


	if (strEvent == "DOWN_P")
	{
		m_shipstates[3] = true;
	}
	if (strEvent == "DOWN_R")
	{
		m_shipstates[3] = false;
	}


	//TODO make a own weapon component
	if (strEvent == "FIRE_P")
	{
		m_shipstates[4] = true;
	}
	if (strEvent == "FIRE_R")
	{
		m_shipstates[4] = false;
	}
}


void ShipMovement::UpdateMovement()
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));


	if(m_shipstates[0]) pPositionComponent->SetRotation(pPositionComponent->GetRotation() + 5);	//rotate right
	if (m_shipstates[1]) pPositionComponent->SetRotation(pPositionComponent->GetRotation() - 5); //rotate left
	if (m_shipstates[2]) m_Direction = sf::Vector2f(0.f, -0.8f); //move forward
	if (m_shipstates[3]) m_Direction = sf::Vector2f(0.f, 0.6f); //move forward
	if (!m_shipstates[2]&& !m_shipstates[3]) m_Direction = sf::Vector2f(0.f, 0.f); //turn off thruster
	if (m_shipstates[4] && m_fWeaponcoolDown<1)
	{
		m_fWeaponcoolDown = m_fFirerate;
		ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateMissile(pPositionComponent, m_Impulses[0])); //shoot rockets
	}
	if (m_fWeaponcoolDown > 0)m_fWeaponcoolDown--;


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

sf::Vector2f ShipMovement::GetMovementVector()
{
	return m_Impulses[0]; // Change to proper m_variable
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
