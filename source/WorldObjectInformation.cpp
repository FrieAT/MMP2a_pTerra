/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#include "WorldObjectInformation.h"

WorldObjectInformation::WorldObjectInformation(EWorldObjectType eType, sf::Vector2f Position, long Size)
: m_eType(eType)
, m_Position(Position)
, m_Size(Size)
, m_bCreated(false)
{
    
}

WorldObjectInformation::~WorldObjectInformation()
{
    
}