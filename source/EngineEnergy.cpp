/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "EngineEnergy.h"
#include "FrameManager.h"
#include "eventbus\EventBus.hpp"
#include "PlayerFuelEvent.h"

EngineEnergy::EngineEnergy(float fMaxFuel, float fFuel)
: m_fEnergy(fFuel)
, m_fMaxEnergy(fMaxFuel)
, m_LastDrained(sf::Clock())
{

}

EngineEnergy::~EngineEnergy()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
}

void EngineEnergy::Init()
{
	FrameManager::GetInstance().RegisterEventObserver(this);
}

float EngineEnergy::GetFuel()
{
	return m_fEnergy;
}

float EngineEnergy::GetMaxFuel()
{
	return m_fMaxEnergy;
}

void EngineEnergy::AddFuel(float fAddFuel)
{
	/*if (fAddFuel < 0.f)
	{
		m_LastDrained.restart();
	}*/
	m_fEnergy += fAddFuel;
	EventBus::FireEvent(PlayerFuelEvent(this, m_fEnergy, this->GetAssignedGameObject()));

	if (m_fEnergy > m_fMaxEnergy)
	{
		m_fEnergy = m_fMaxEnergy;
	}
	else if (m_fEnergy < 0.f)
	{
		m_fEnergy = 0.f;
	}
}

void EngineEnergy::OnFrameUpdate(sf::Time DeltaTime)
{
	//if ((m_LastDrained.getElapsedTime()).asSeconds() >= 2.5f)
	//{
	AddFuel(20.f * DeltaTime.asSeconds());
	//}
}

void EngineEnergy::Serialize(SerializeNode * pParentNode)
{
	IEngine::Serialize(pParentNode);
	pParentNode->AddElement(new SerializeNode("Energy", ESerializeNodeType::Property, std::to_string(m_fEnergy)));
	pParentNode->AddElement(new SerializeNode("MaxEnergy", ESerializeNodeType::Property, std::to_string(m_fMaxEnergy)));
}

IComponent * EngineEnergy::Deserialize(SerializeNode * pNode)
{
	EngineEnergy* pComponent = new EngineEnergy(0.f);

	IEngine::Deserialize(pNode, pComponent);

	pComponent->m_fEnergy = stof((pNode->GetNode("Energy"))->GetValue());
	pComponent->m_fMaxEnergy = stof((pNode->GetNode("MaxEnergy"))->GetValue());

	return pComponent;
}
