/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

class SerializeNode;

class INodeVisitor
{
public:
    virtual void Visit(SerializeNode* pNode) = 0;
};