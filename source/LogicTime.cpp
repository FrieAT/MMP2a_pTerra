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
	if (m_fRemainingTime <= 0)
	{
		// GameOver
		Game::m_pEngine->ChangeState(EGameState::GameStateGameOver);
	}
}
