#pragma once

#include "IMovement.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "IInputObserver.h"
#include "IFrameObserver.h"
#include "IPosition.h"
#include "GameObject.h"

class ShipMovement : public IMovement, public IInputObserver, public IFrameObserver
{
public:
	ShipMovement(char cPlayer);
	~ShipMovement();
    void Init();
	void OnInputUpdate(std::string strEvent);
	void OnFrameUpdate(sf::Time DeltaTime);
	void UpdateMovement(sf::Time DeltaTime);
    void Serialize(SerializeNode* pParentNode);
    static IComponent* Deserialize(SerializeNode* pNode);
    std::string GetComponentName() { return std::string("ShipMovement"); }
	void setShipState(int State, bool value);
	bool getShipState(int State);
	void SetMass(float mass);
	void SetFirerate(float Firerate);
private:
	char m_cPlayer;	//player id for multiple playercontrolled ships
	float m_fFirerate;
	float m_fWeaponcoolDown = 0.f;
	sf::Vector2f m_Direction;
	std::vector<bool> m_ShipState;
};

