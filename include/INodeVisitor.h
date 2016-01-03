/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include "SerializeNode.h"

class INodeVisitor
{
public:
    virtual void Visit(SerializeNode* pNode) = 0;
};