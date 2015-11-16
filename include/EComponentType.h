//
//  EComponentType.h
//  MMP2a_SpaceGame
//
//  Created by Friedrich Schmidt on 14.11.15.
//  Copyright © 2015 Friedrich Schmidt. All rights reserved.
//

#ifndef EComponentType_h
#define EComponentType_h

enum class EComponentType
{
    // Offset begins at 1
    Position,
    Movement,
    Health,
    Collision,
    Drawing,
    // ... add here more Component-Types
    
    MaxItem, // Do not delete or move this line, because it defines the amount of Components.
};

#endif /* EComponentType_h */
