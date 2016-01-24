#pragma once

#include "IAIState.h"

class AIStateFlee : public IAIState
{
public:
	AIStateFlee();
	~AIStateFlee();
	virtual void Update(GameObject* obj);
};

