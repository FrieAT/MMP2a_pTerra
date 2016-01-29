/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "eventbus/Event.hpp"
#include "GameObject.h"

class PlayerDamageEvent : public Event
{
public:
	PlayerDamageEvent(IComponent* sender, GameObject* const gameObject, const float health, const float shield, const float damage) :
		Event(sender),
		m_player(gameObject),
		m_health(health),
		m_shield(shield),
		m_damage(damage)
	{

	}

	virtual ~PlayerDamageEvent()
	{

	}

	GameObject* const GetPlayer()
	{
		return m_player;
	}

	float const GetHealth()
	{
		return m_health;
	}

	float const GetShield()
	{
		return m_shield;
	}

	float const GetDamage()
	{
		return m_damage;
	}

private:
	GameObject* const m_player;
	const float m_health;
	const float m_shield;
	const float m_damage;
};