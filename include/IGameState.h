/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

class IGameState
{
public:
	virtual ~IGameState() { }
    
    virtual void Init() = 0;
    // virtual void Pause() = 0; // TODO: Implementation
    // virtual void Resume() = 0; // TODO: Implementation
};