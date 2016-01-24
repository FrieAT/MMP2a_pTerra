/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "eventbus/Event.hpp"
#include "GameObject.h"

class PlayerFuelEvent : public Event
{
public:
		PlayerFuelEvent(IComponent* sender, float fuel, GameObject* const receiver) :
		Event(sender),
		m_fuel(fuel),
		m_receiver(receiver)
	{

	}

	virtual ~PlayerFuelEvent()
	{

	}

	int const GetFuel()
	{
		return m_fuel;
	}

	GameObject* const GetReceiver()
	{
		return m_receiver;
	}

private:
	float const m_fuel;
	GameObject* const m_receiver;
};