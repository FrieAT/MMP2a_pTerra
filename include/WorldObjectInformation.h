/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <SFML/Graphics.hpp>

#include "EWorldObjectType.h"

class WorldObjectInformation
{
public:
    WorldObjectInformation(EWorldObjectType eType, sf::Vector2f Position, sf::Vector2f Size);
    ~WorldObjectInformation();
    EWorldObjectType GetWorldObjectType() { return m_eType; }
    sf::Vector2f GetPosition() { return m_Position; }
    sf::Vector2f GetSize() { return m_Size; }
private:
    EWorldObjectType m_eType;
    sf::Vector2f m_Position;
    sf::Vector2f m_Size;
    bool m_bCreated;
};