/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "EWorldObjectType.h"

class WorldObjectInformation
{
public:
    WorldObjectInformation(EWorldObjectType eType, sf::Vector2f Position, long Size);
    ~WorldObjectInformation();
    EWorldObjectType GetWorldObjectType() { return m_eType; }
    sf::Vector2f GetPosition() { return m_Position; }
    long GetSize() { return m_Size; }
private:
    EWorldObjectType m_eType;
    sf::Vector2f m_Position;
    long m_Size;
    bool m_bCreated;
};