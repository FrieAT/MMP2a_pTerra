#pragma once

#include <SFML/Graphics.hpp>

#include "IKI.h"
#include "IInputObserver.h"
#include "IKIObserver.h"
#include "KIManager.h"

class PatrolKI : public IKI, public IKIObserver
{
public:
	//   LinearMovement(float fRotation, sf::Vector2f ShipSpeed);
	//LinearMovement(float fRotation, float fSpeed);
	PatrolKI();
	~PatrolKI();
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
