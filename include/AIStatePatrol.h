#pragma once

#include "IAIState.h"

class AIStatePatrol : public IAIState
{
public:
	AIStatePatrol();
	~AIStatePatrol();
	virtual void Update(GameObject* obj);
private:
	float m_nextAngle;
	int m_Timer;
};

