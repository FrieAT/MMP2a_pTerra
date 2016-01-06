#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "IAI.h"
#include "IInputObserver.h"
#include "IAIObserver.h"
#include "AIManager.h"

class PatrolAI : public IAI, public IAIObserver
{
public:
	//   LinearMovement(float fRotation, sf::Vector2f ShipSpeed);
	//LinearMovement(float fRotation, float fSpeed);
	PatrolAI();
	~PatrolAI();
	void Init();
	void Update();
	void Serialize(SerializeNode* pParentNode);
	static IComponent* Deserialize(SerializeNode* pNode);
	std::string GetComponentName() { return std::string("PatrolKI"); }

private:
	int m_Timer = 25;
	int m_FacingAngle = 90;
	sf::Vector2f m_FlyTo = sf::Vector2f(0,0);
	bool m_target = true;
};
