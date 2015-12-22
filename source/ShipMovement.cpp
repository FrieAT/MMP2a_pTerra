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

	mass = 5;
	invMass = 1 / mass;

	m_ShipState = std::vector<bool>(5, false);
	m_fSpeed = 500.f;
	m_fMaxSpeed = 2000;
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
		m_ShipState[0] = true;
	}
	if (strEvent == "RIGHT_R")
	{
		m_ShipState[0] = false;
	}


	if (strEvent == "LEFT_P")
	{
		m_ShipState[1] = true;
	}
	if (strEvent == "LEFT_R")
	{
		m_ShipState[1] = false;
	}


	if (strEvent == "UP_P")
	{
		m_ShipState[2] = true;
	}
	if (strEvent == "UP_R")
	{
		m_ShipState[2] = false;
	}


	if (strEvent == "DOWN_P")
	{
		m_ShipState[3] = true;
	}
	if (strEvent == "DOWN_R")
	{
		m_ShipState[3] = false;
	}


	//TODO make a own weapon component
	if (strEvent == "FIRE_P")
	{
		m_ShipState[4] = true;
	}
	if (strEvent == "FIRE_R")
	{
		m_ShipState[4] = false;
	}
}


void ShipMovement::UpdateMovement()
{
	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));


	if(m_ShipState[0]) pPositionComponent->SetRotation(pPositionComponent->GetRotation() + 5);	//rotate right
	if (m_ShipState[1]) pPositionComponent->SetRotation(pPositionComponent->GetRotation() - 5); //rotate left
	if (m_ShipState[2]) m_Direction = sf::Vector2f(0.f, -0.8f); //move forward
	if (m_ShipState[3]) m_Direction = sf::Vector2f(0.f, 0.6f); //move forward
	if (!m_ShipState[2]&& !m_ShipState[3]) m_Direction = sf::Vector2f(0.f, 0.f); //turn off thruster
	if (m_ShipState[4] && m_fWeaponcoolDown<1)
	{
		m_fWeaponcoolDown = m_fFirerate;
		ObjectManager::GetInstance().AddGameObject(GameObjectFactory::CreateMissile(pPositionComponent, velocity)); //shoot rockets
		std::cout << velocity.x << " "<<velocity.y << std::endl;
	}
	if (m_fWeaponcoolDown > 0)m_fWeaponcoolDown--;



	//if (fSpeed >= m_fMaxSpeed)
	//{
	//	m_Impulses[0] = m_Impulses[0] * 0.99f;
	//}

	//std::cout << speed << std::endl;

}



void ShipMovement::OnFrameUpdate(sf::Time DeltaTime)
{
	UpdateMovement();

	IPosition* pPositionComponent = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));
	sf::Vector2f forces;

	sf::Transform RotationMatrix = sf::Transform::Identity;
	RotationMatrix.rotate(pPositionComponent->GetRotation());

	sf::Vector2f accVec = RotationMatrix * m_Direction *m_fSpeed;

	auto length2 = [](const sf::Vector2f &vec) -> float { return vec.x * vec.x + vec.y * vec.y; };	//calculate vectorlenght squared

	float squaredSpeedLimit = m_fMaxSpeed * m_fMaxSpeed;
	if (length2(velocity + accVec * DeltaTime.asSeconds()) < squaredSpeedLimit)
		impulses.push_back(accVec);

	for (const auto& f : impulses)
		forces += f;
	impulses.clear();

	acceleration = forces * invMass;
	velocity += acceleration * DeltaTime.asSeconds();
	//body.velocity = body.velocity * 0.99f; //< simple "friction"

	pPositionComponent->SetPosition(pPositionComponent->GetPosition() + velocity * DeltaTime.asSeconds());

}
