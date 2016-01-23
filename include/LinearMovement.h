#pragma once

#include "IMovement.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "IInputObserver.h"
#include "IFrameObserver.h"

class LinearMovement : public IMovement, public IFrameObserver
{
public:
 //   LinearMovement(float fRotation, sf::Vector2f ShipSpeed);
	//LinearMovement(float fRotation, float fSpeed);
	LinearMovement(float fRotation, float fSpeed, float fmass, sf::Vector2f fStartSpeed = sf::Vector2f(0,0), bool bAccelerating = false);
    ~LinearMovement();
    void Init();
    void OnFrameUpdate(sf::Time DeltaTime);
    void Serialize(SerializeNode* pParentNode);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("LinearMovement"); }
private:
	sf::Vector2f m_Direction;
	float m_fRotation = 0.f;
	bool m_bAccelerating;
};
