/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "IGUI.h"
#include "IDrawing.h"
#include "eventbus\EventHandler.hpp"
#include "PlayerDamageEvent.h"
#include "PlayerShieldRegenerationEvent.h"
#include "ScoreEvent.h"
#include "PlayerFuelEvent.h"
#include "IDrawing.h"

class GUIPlayerStatus : public IGUI, public EventHandler<PlayerDamageEvent>, public EventHandler<PlayerShieldRegenerationEvent>, public EventHandler<ScoreEvent>, public EventHandler<PlayerFuelEvent>
{
public:
	GUIPlayerStatus(tgui::Gui& gui) : IGUI(gui)
	{
		Init();
	}
	~GUIPlayerStatus();
	void Init();
	void onEvent(PlayerDamageEvent* e) override;
	void onEvent(PlayerShieldRegenerationEvent* e) override;
	void onEvent(ScoreEvent* e) override;
	void onEvent(PlayerFuelEvent* e) override;

private:
	std::shared_ptr<tgui::ProgressBar> m_HealthBar;
	std::shared_ptr<tgui::ProgressBar> m_ShieldBar;
	std::shared_ptr<tgui::ProgressBar> m_EnergyBar;
	std::shared_ptr<tgui::Label> m_Health;
	std::shared_ptr<tgui::Label> m_Shield;
	std::shared_ptr<tgui::Label> m_Energy;
	std::shared_ptr<tgui::Label> m_Score;
};

