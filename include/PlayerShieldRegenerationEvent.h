/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "eventbus/Event.hpp"
#include "GameObject.h"

class PlayerShieldRegenerationEvent : public Event
{
public:
	PlayerShieldRegenerationEvent(IComponent* sender, GameObject* const gameObject, const float shield) :
		Event(sender),
		m_player(gameObject),
		m_shield(shield)
	{

	}

	virtual ~PlayerShieldRegenerationEvent()
	{

	}

	GameObject* const GetPlayer()
	{
		return m_player;
	}

	float const GetShield()
	{
		return m_shield;
	}

private:
	GameObject* const m_player;
	const float m_shield;
};