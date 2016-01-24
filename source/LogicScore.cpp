/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#include "stdafx.h"

#include "LogicScore.h"
#include "IScore.h"
#include "ICollision.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "INavigation.h"
#include "IPosition.h"

void LogicScore::Init()
{
	ICollision* pCollisionComponent = static_cast<ICollision*>(GetAssignedGameObject()->GetComponent(EComponentType::Collision));
	if (pCollisionComponent == nullptr)
	{
		throw std::runtime_error("LogicPowerUpScore component needs from assigned gameobject a ICollision-component.");
	}
	pCollisionComponent->m_bPhysicsApplyable = false; // Let ignore physics from object.

	CollisionManager::GetInstance().RegisterCollisionEvent(this, GetAssignedGameObject());
}

LogicScore::~LogicScore()
{
	CollisionManager::GetInstance().UnregisterCollisionEvent(this, GetAssignedGameObject());
}

void LogicScore::Action(GameObject* pPossibleOther)
{
	if (pPossibleOther == nullptr)
	{
		throw std::runtime_error("LogicPowerUp needs a pPossibleOther defined GameObject. Null-Reference-Found!");
	}

	// Check if it is the player-ship /(cuz for enemy it isn´t needed)
	if (pPossibleOther->GetID().compare("ship") != 0)
	{
		return;
	}

	// If own game-object has no IScore-Component, than give exception.
	// Because LogicPowerUpScore needs a IScore.
	IScore* pOwnScoreComponent = static_cast<IScore*>(GetAssignedGameObject()->GetComponent(EComponentType::Score));
	if (pOwnScoreComponent == nullptr)
	{
		throw std::runtime_error("LogicPowerUpScore needs from assigned game-object a IScore component!");
	}

	IScore* pOtherScoreComponent = static_cast<IScore*>(pPossibleOther->GetComponent(EComponentType::Score));
	if (pOtherScoreComponent == nullptr)
	{
		// Ignore game-objects, which doesn´t have a IScore-Component.
		return;
	}

	// Add own points to OtherGameObject and remove own Score.
	pOtherScoreComponent->AddScore(pOwnScoreComponent->GetScore());
	
	// Remove Logic, so it isn´t called again.
	GetAssignedGameObject()->RemoveComponent(EComponentType::Logic);

	return;
}

void LogicScore::OnCollisionEvent(GameObject * pOther, sf::Vector2f ImpulseImpact)
{
	if (pOther != nullptr)
	{
		Action(pOther);
	}
}
