/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <map>
#include <string>

#include "ESerializeNodeType.h"

class SerializeNode
{
public:
    SerializeNode(std::string strName, ESerializeNodeType eNodeType, std::string strValue = "");
    ~SerializeNode();
    void AddElement(SerializeNode* pNode);
    void RemoveElement(SerializeNode* pNode);
private:
    ESerializeNodeType m_eNodeType;
    std::string m_strName;
    std::string m_strValue;
    std::map<std::string, SerializeNode*> m_Elements;
};