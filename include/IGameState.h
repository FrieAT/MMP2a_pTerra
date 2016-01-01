/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

class IGameState
{
public:
	virtual ~IGameState() { }

    virtual void Init() = 0;
	virtual void Update(sf::Time DeltaTime, sf::RenderWindow* pWindow) = 0;
};