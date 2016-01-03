/*=================================================================
 Copyright (c) MultiMediaTechnology, 2015
 =================================================================*/

#pragma once

#include <map>
#include <string>

#include "ESerializeNodeType.h"
#include "INodeVisitor.h"

class SerializeNode
{
public:
    SerializeNode(std::string strName, ESerializeNodeType eNodeType, std::string strValue = "");
    ~SerializeNode();
    void AddElement(SerializeNode* pNode);
    void RemoveElement(SerializeNode* pNode);
    SerializeNode* GetNode(std::string strName);
    std::string GetName() { return m_strName; }
    std::string GetValue();
    std::map<std::string, SerializeNode*> GetChildren() { return m_Elements; }
    ESerializeNodeType GetType() { return m_eNodeType; }
    void Accept(INodeVisitor Visitor);
private:
    ESerializeNodeType m_eNodeType;
    std::string m_strName;
    std::string m_strValue;
    std::map<std::string, SerializeNode*> m_Elements;
};