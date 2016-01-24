#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "IAI.h"
#include "IInputObserver.h"
#include "IAIObserver.h"
#include "AIManager.h"
#include "IAIState.h"

class SimpleAI : public IAI, public IAIObserver
{
public:
	//   LinearMovement(float fRotation, sf::Vector2f ShipSpeed);
	//LinearMovement(float fRotation, float fSpeed);
	SimpleAI();
	~SimpleAI();
	void Init();
	void Update();
	std::string GetComponentName() { return std::string("SimpleAI"); }

private:
	IAIState* m_CurrentState;
	std::vector<IAIState*> m_AIStates;
};
