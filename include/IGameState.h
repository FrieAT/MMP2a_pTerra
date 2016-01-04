/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

class IGameState
{
public:
	virtual ~IGameState() { }

    virtual void Init(sf::RenderWindow* pWindow) = 0;
	virtual void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow) = 0;

protected:
	tgui::Gui m_Gui;
};