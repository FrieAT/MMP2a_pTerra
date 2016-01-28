/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "LogicTime.h"
#include "IScore.h"
#include "ICollision.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "INavigation.h"
#include "IPosition.h"
#include "FrameManager.h"
#include "eventbus\EventBus.hpp"
#include "TimerEvent.h"
#include "Game.h"

LogicTime::LogicTime(int iTimelimitSeconds)
: m_fRemainingTime(static_cast<float>(iTimelimitSeconds))
{

}

void LogicTime::Init()
{
	FrameManager::GetInstance().RegisterEventObserver(this);
}

LogicTime::~LogicTime()
{
	FrameManager::GetInstance().UnregisterEventObserver(this);
}

void LogicTime::Action(GameObject* pPossibleOther)
{
	// Do here nothing.
	return;
}

void LogicTime::OnFrameUpdate(sf::Time DeltaTime)
{
	m_fRemainingTime -= DeltaTime.asSeconds();
	EventBus::FireEvent(TimerEvent(this, static_cast<int>(m_fRemainingTime)));
	if (m_fRemainingTime <= 0)
	{
		// GameOver
		Game::m_pEngine->ChangeState(EGameState::GameStateGameOver);
	}
}

void LogicTime::Serialize(SerializeNode* pParentNode)
{
	this->IComponent::Serialize(pParentNode);

	pParentNode->AddElement(new SerializeNode("TimeLeft", ESerializeNodeType::Property, std::to_string(m_fRemainingTime)));
}

IComponent* LogicTime::Deserialize(SerializeNode* pNode)
{
	LogicTime* pComponent = new LogicTime(0);

	ILogic::Deserialize(pNode, pComponent);

	pComponent->m_fRemainingTime = stof((pNode->GetNode("TimeLeft"))->GetValue());

	return pComponent;
}