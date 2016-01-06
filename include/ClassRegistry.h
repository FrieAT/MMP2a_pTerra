/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <map>
#include <string>

#include "BoxCollision.h"
#include "CircleCollision.h"
#include "HealthShip.h"
#include "HealthMissile.h"
#include "HealthAsteroid.h"
#include "SpriteDrawing.h"
#include "FontDrawing.h"
#include "StaticView.h"
#include "DynamicView.h"
#include "PixelPosition.h"
#include "QuadrantPosition.h"
#include "LinearMovement.h"
#include "ShipMovement.h"
#include "NavigationCursor.h"
#include "ResearchScore.h"
#include "PatrolKI.h"

#define REGISTER_COMPONENT(ComponentName) \
    ClassRegistry::GetInstance().RegisterComponent(std::string(""#ComponentName""), ComponentName::Deserialize);

class IComponent;
class SerializeNode;

class ClassRegistry
{
public:
    static ClassRegistry& GetInstance()
    {
        static ClassRegistry g_Instance;
        return g_Instance;
    }
    void Init()
    {
        REGISTER_COMPONENT(BoxCollision);
        REGISTER_COMPONENT(CircleCollision);
        REGISTER_COMPONENT(HealthShip);
        REGISTER_COMPONENT(HealthMissile);
        REGISTER_COMPONENT(HealthAsteroid);
        REGISTER_COMPONENT(SpriteDrawing);
        REGISTER_COMPONENT(FontDrawing);
        REGISTER_COMPONENT(StaticView);
        REGISTER_COMPONENT(DynamicView);
        REGISTER_COMPONENT(PixelPosition);
        REGISTER_COMPONENT(QuadrantPosition);
        REGISTER_COMPONENT(LinearMovement);
        REGISTER_COMPONENT(ShipMovement);
        REGISTER_COMPONENT(NavigationCursor);
        REGISTER_COMPONENT(ResearchScore);
	REGISTER_COMPONENT(PatrolKI);
    }
    void RegisterComponent(std::string strClassName, IComponent* (*ComponentConstructor)(SerializeNode* pNode))
    {
        ClassRegistry* instance = &this->GetInstance();
        auto it = instance->m_ComponentConstructors.find(strClassName);
        if(it != instance->m_ComponentConstructors.end())
        {
            throw std::runtime_error("ClassName already defined.");
        }
        instance->m_ComponentConstructors[strClassName] = ComponentConstructor;
    }
    IComponent* CreateComponent(std::string strComponentName, SerializeNode* pNode)
    {
        auto it = m_ComponentConstructors.find(strComponentName);
        if(it == m_ComponentConstructors.end())
        {
            throw std::runtime_error("Undefined Component-Class-Name.");
        }
        return CreateComponent(it->second, pNode);
    }
    IComponent* CreateComponent(IComponent* (*ComponentConstructor)(SerializeNode* pNode), SerializeNode* pNode)
    {
        return ComponentConstructor(pNode);
    }
private:
    ClassRegistry() { }
    ClassRegistry(const ClassRegistry&) = delete;
    void operator= (const ClassRegistry&) = delete;
    std::map<std::string, IComponent* (*)(SerializeNode* pNode)> m_ComponentConstructors;
};