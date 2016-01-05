/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include <TGUI/TGUI.hpp>

class IGameState
{
public:
	virtual ~IGameState() { }

    virtual void Init(sf::RenderWindow* pWindow) = 0;
	virtual void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow) = 0;
	virtual bool ClearOnGameStateChange() { return m_bClearOnGameStateChange; };
	virtual bool IsInitialized() { return m_bIsInitialized; };

protected:
	tgui::Gui m_Gui;
	bool m_bClearOnGameStateChange = true;
	bool m_bIsInitialized = false;
};