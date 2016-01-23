/*=================================================================
Copyright (c) MultiMediaTechnology, 2015
=================================================================*/

#pragma once

#include "EComponentType.h"
#include "SerializeNode.h"

class IComponent;

class GameObject
{
public:
	GameObject(std::string strID);
	~GameObject();

	std::string GetID();
	void SetComponent(IComponent* pComponent);
	void RemoveComponent(EComponentType eComponentType);
	IComponent* GetComponent(EComponentType eComponentType);
    int GetAmountOfUsedComponentTypes();
    bool IsInFreezedState();
    SerializeNode* Serialize();
    static GameObject* Deserialize(SerializeNode* pNode);
    void SetTemporaryState(bool bTemporary) { m_bTemporaryCreated = bTemporary; }
    bool GetTemporaryState() { return m_bTemporaryCreated; }
    void SetAssistedState(bool bAssisted) { m_bAssistedCreated = bAssisted; }
    bool GetAssistedState() { return m_bAssistedCreated; }
private:
	std::string m_strID;
	std::unordered_map<EComponentType, IComponent*> m_Components;
    bool m_bTemporaryCreated;
    bool m_bAssistedCreated;
};
