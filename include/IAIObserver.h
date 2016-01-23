/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

class IAIObserver
{
public:
	~IAIObserver() { }
	virtual void Update() = 0;
};