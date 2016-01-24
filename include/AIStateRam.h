#pragma once

#include "IAIState.h"

class AIStateRam : public IAIState
{
public:
	AIStateRam();
	~AIStateRam();
	virtual void Update(GameObject* obj);
};

