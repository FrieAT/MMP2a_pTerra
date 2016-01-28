#include "stdafx.h"

#include "SimpleAI.h"
#include "IPosition.h"
#include "ShipMovement.h"
#include "ObjectManager.h"
#include "IHealth.h"

#include "AIStatePatrol.h"
#include "AIStateFlee.h"
#include "AIStateRam.h"

SimpleAI::SimpleAI()
{
	m_AIStates.push_back(new AIStateFlee);
	m_AIStates.push_back(new AIStatePatrol);
	m_AIStates.push_back(new AIStateRam);
	m_CurrentState = m_AIStates[1];	//Patrol
}

SimpleAI::~SimpleAI()
{
	for (auto itr = m_AIStates.begin(); itr != m_AIStates.end(); itr++)
	{
		delete *itr;
	}
	m_AIStates.clear();

	AIManager::GetInstance().UnregisterAIObserver(this);
}

void SimpleAI::Init()
{
	AIManager::GetInstance().RegisterAIObserver(this);
}

void SimpleAI::Update()
{
	IPosition* pPos = static_cast<IPosition*>(GetAssignedGameObject()->GetComponent(EComponentType::Position));

	ShipMovement* pmov = static_cast<ShipMovement*>(GetAssignedGameObject()->GetComponent(EComponentType::Movement));


	auto length = [](const sf::Vector2f &vec) -> float { return std::sqrt(vec.x * vec.x + vec.y * vec.y); };	//calculate vectorlenght squared

	IPosition* pPlayerPos = static_cast<IPosition*>(ObjectManager::GetInstance().GetPlayer()->GetComponent(EComponentType::Position));
	
	float playerDistance = length(pPlayerPos->GetPosition() - pPos->GetPosition());
	float health = static_cast<IHealth*>(GetAssignedGameObject()->GetComponent(EComponentType::Health))->GetHealth();


	// Pseudo State Pattern (All m_AIStates have to check player distance and AI ship health.. so no real state pattern at all
	//delete m_CurrentState;

	pmov->setShipState(0, false);
	pmov->setShipState(1, false);
	pmov->setShipState(2, false);
	pmov->setShipState(3, false);
	pmov->setShipState(4, false);

	if (playerDistance < 1500.f)
	{
		if (health < 50.f)
		{
			m_CurrentState = m_AIStates[0]; //Flee
		}
		else
		{
			m_CurrentState = m_AIStates[2];	//Ram
		}
	}
	else
	{
		m_CurrentState = m_AIStates[1];	//Patrol
	}

 m_CurrentState->Update(GetAssignedGameObject());
}

void SimpleAI::Serialize(SerializeNode* pParentNode)
{
	IAI::Serialize(pParentNode);


}

IComponent* SimpleAI::Deserialize(SerializeNode* pNode)
{
	SimpleAI* pComponent = new SimpleAI();

	IAI::Deserialize(pNode, pComponent);

	return pComponent;
}