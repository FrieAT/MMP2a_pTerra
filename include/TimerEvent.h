/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "eventbus/Event.hpp"
#include "GameObject.h"

class TimerEvent : public Event
{
public:
	TimerEvent(IComponent* sender, int seconds) :
		Event(sender),
		m_seconds(seconds)
	{

	}

	~TimerEvent()
	{

	}

	int const GetSeconds()
	{
		return m_seconds;
	}

private:
	int const m_seconds;
};