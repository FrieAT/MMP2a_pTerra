/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "eventbus/Event.hpp"
#include "GameObject.h"

class ScoreEvent : public Event
{
public:
	ScoreEvent(IComponent* sender, int score, GameObject* const receiver, GameObject* const giver) :
		Event(sender),
		m_score(score),
		m_receiver(receiver),
		m_giver(giver)
	{

	}

	~ScoreEvent()
	{

	}

	int const GetScore()
	{
		return m_score;
	}

	GameObject* const GetReceiver()
	{
		return m_receiver;
	}

	GameObject* const GetGiver()
	{
		return m_giver;
	}

private:
	int const m_score;
	GameObject* const m_receiver;
	GameObject* const m_giver;
};