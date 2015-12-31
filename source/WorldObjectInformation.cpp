/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "WorldObjectInformation.h"

WorldObjectInformation::WorldObjectInformation(EWorldObjectType eType, sf::Vector2f Position, sf::Vector2f Size)
: m_eType(eType)
, m_Position(Position)
, m_Size(Size)
{
    
}

WorldObjectInformation::~WorldObjectInformation()
{
    
}